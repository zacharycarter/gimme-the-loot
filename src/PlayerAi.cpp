#include "Attacker.hpp"
#include "Container.hpp"
#include "Destructible.hpp"
#include "Engine.hpp"
#include "Pickable.hpp"
#include "PlayerAi.hpp"

PlayerAi::~PlayerAi() {
}

void PlayerAi::update(Actor *owner) {
  if (owner->destructible && owner->destructible->isDead()) {
    return;
  }
  int dx=0, dy=0;
  switch(engine.lastKey.vk) {
  case TCODK_UP : 
    dy = -1;
    break;
  case TCODK_DOWN :
    dy = 1;
    break;
  case TCODK_LEFT :
    dx = -1;
    break;
  case TCODK_RIGHT :
    dx = 1;
    break;
  case TCODK_CHAR :
    handleActionKey(owner, engine.lastKey.c);
    break;
  default :
    break;
  }
  if (dx != 0 || dy != 0) {
    engine.gameStatus = Engine::NEW_TURN;
    if (moveOrAttack(owner, owner->x + dx, owner->y + dy)) {
      engine.map->computeFov();
    }
  }
}

bool PlayerAi::moveOrAttack(Actor *owner, int targetx, int targety) {
  if (engine.map->isWall(targetx, targety)) return false;
  for (Actor **iterator = engine.actors.begin();
       iterator != engine.actors.end(); iterator++) {
    Actor *actor = *iterator;
    if (actor->destructible && !actor->destructible->isDead()
	&& actor->x == targetx && actor->y == targety) {
      owner->attacker->attack(owner, actor);
      return false;
    }
  }
  for (Actor **iterator = engine.actors.begin();
       iterator != engine.actors.end(); iterator++) {
    Actor *actor = *iterator;
    bool corpseOrItem = (actor->destructible && actor->destructible->isDead())
      || actor->pickable;
    if (corpseOrItem
	&& actor->x == targetx && actor->y == targety) {
      engine.gui->message(TCODColor::lightGrey,"There's a %s here",actor->name);
    }
  }
  owner->x=targetx;
  owner->y=targety;
  return true;
}

Actor *PlayerAi::choseFromInventory(Actor *owner) {
  static const int INVENTORY_WIDTH = 50;
  static const int INVENTORY_HEIGHT = 28;
  static TCODConsole con(INVENTORY_WIDTH, INVENTORY_HEIGHT);
  con.setDefaultForeground(TCODColor::white);
  con.printFrame(0,0,INVENTORY_WIDTH,INVENTORY_HEIGHT,true,
		 TCOD_BKGND_DEFAULT, "inventory");
  con.setDefaultForeground(TCODColor::white);
  int shortcut = 'a';
  int y = 1;
  for (Actor **it = owner->container->inventory.begin();
       it != owner->container->inventory.end(); it++) {
    Actor *actor = *it;
    con.print(2,y,"(%c) %s", shortcut, actor->name);
    y++;
    shortcut++;
  }
  TCODConsole::blit(&con, 0, 0, INVENTORY_WIDTH, INVENTORY_HEIGHT,
		    TCODConsole::root, engine.screenWidth/2 - INVENTORY_WIDTH/2,
		    engine.screenHeight/2 - INVENTORY_HEIGHT/2);
  TCODConsole::flush();
  TCOD_key_t key;
  TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
  if (key.vk == TCODK_CHAR) {
    int actorIndex = key.c - 'a';
    if (actorIndex >= 0 && actorIndex < owner->container->inventory.size()) {
      return owner->container->inventory.get(actorIndex);
    }
  }
  return NULL;
}

void PlayerAi::handleActionKey(Actor *owner, int ascii) {
  switch(ascii) {
  case 'g' :
    {
      bool found = false;
      for (Actor **iterator = engine.actors.begin();
	   iterator != engine.actors.end(); iterator++) {
	Actor *actor = *iterator;
	if (actor->pickable && actor->x == owner->x && actor->y == owner->y) {
	  if (actor->pickable->pick(actor, owner)) {
	    found = true;
	    engine.gui->message(TCODColor::lightGrey, "You pick up the %s.",
				actor->name);
	    break;
	  } else if (!found) {
	    found = true;
	    engine.gui->message(TCODColor::red, "Your inventory is full.");
	  }
	}
      }
      if (!found) {
	engine.gui->message(TCODColor::lightGrey, "There's nothing here to interact with.");
      }
      engine.gameStatus = Engine::NEW_TURN;
    }
    break;
  case 'i' :
    {
      Actor *actor = choseFromInventory(owner);
      if (actor) {
	actor->pickable->use(actor,owner);
	engine.gameStatus = Engine::NEW_TURN;
      }
    }
    break;
  case 'd' :
    {
      Actor *actor = choseFromInventory(owner);
      if (actor) {
	actor->pickable->drop(actor,owner);
	engine.gameStatus=Engine::NEW_TURN;
      }
    }
    break;
  }
}
