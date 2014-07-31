#include <iostream>
#include <fstream>
#include "Attacker.hpp"
#include "Container.hpp"
#include "PlayerAi.hpp"
#include "PlayerDestructible.hpp"
#include "gmtl.pb.h"
#include "Engine.hpp"
using namespace std;

Engine::Engine(int screenWidth, int screenHeight) : gameStatus(STARTUP),fovRadius(10),screenWidth(screenWidth),screenHeight(screenHeight),level(1) {
    TCODConsole::initRoot(screenWidth,screenHeight,"gimme-the-loot",false);
    gui = new Gui();
}

Engine::~Engine() {
  reinit();
  delete gui;
  google::protobuf::ShutdownProtobufLibrary();
}

void Engine::reinit() {
  actors.clearAndDelete();
  if (map) delete map;
  gui->clear();
}

void Engine::init() {
  player = new Actor(40,25,'@',"player",TCODColor::white);
  player->destructible=new PlayerDestructible(30,2,"your corpse");
  player->attacker=new Attacker(5);
  player->ai = new PlayerAi();
  player->container = new Container(26);
  actors.push(player);
  stairs = new Actor(0,0,'>',"stairs",TCODColor(196,77,88));
  stairs->blocks = false;
  stairs->fovOnly = false;
  actors.push(stairs);
  map = new Map(80,43);
  map->init(true);
  gui->logEntry(TCODColor::green,"welcome!");
  gameStatus = STARTUP;
}

void Engine::update() {
  if ( gameStatus == STARTUP ) map->computeFov();
  gameStatus=IDLE;
  TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,&mouse);
  if ( lastKey.vk == TCODK_ESCAPE ) {
    save();
    load();
  }
  player->update();
  if ( gameStatus == NEW_TURN ) {
    for (Actor **iterator=actors.begin(); iterator != actors.end();
	 iterator++) {
      Actor *actor=*iterator;
      if ( actor != player ) {
	actor->update();
      }
    }
  }
}

void Engine::render() {
  TCODConsole::root->clear();
  map->render();
  for (Actor **iterator = actors.begin();
       iterator != actors.end(); iterator++) {
    Actor *actor = *iterator;
    if (actor != player 
	&& ((!actor->fovOnly && map->isExplored(actor->x, actor->y))
	    || map->isInFov(actor->x, actor->y))) {
      actor->render();
    }
  }
  player->render();
  gui->render();

  TCODConsole::root->setDefaultForeground(TCODColor::gold);
  TCODConsole::root->print(1, screenHeight-2, "Gold : %d", 
			   (int)player->container->gold);
}

void Engine::nextLevel() {
  level++;

  gui->logEntry(TCODColor::lightViolet,"You take a moment to rest, and recover your strength.");
  player->destructible->heal(player->destructible->maxHp/2);
  gui->logEntry(TCODColor::red,"After a rare moment of peace, you descend\ndeeper into the heart of the dungeon...");

  delete map;
  // delete all actors but player and stairs
  for (Actor **it=actors.begin(); it!=actors.end(); it++) {
    if ( *it != player && *it != stairs ) {
      delete *it;
      it = actors.remove(it);
    }
  }

  map = new Map(80,43);
  map->init(true);
  gameStatus=STARTUP;
}

void Engine::sendToBack(Actor *actor) {
  actors.remove(actor);
  actors.insertBefore(actor,0);
}

Actor *Engine::getClosestMonster(int x, int y, float range) const {
  Actor *closest = NULL;
  float bestDistance = 1E6f;

  for (Actor **iterator = actors.begin();
       iterator != actors.end(); iterator++) {
    Actor *actor = *iterator;
    if (actor != player && actor->destructible
	&& !actor->destructible->isDead()) {
      float distance = actor->getDistance(x,y);
      if (distance < bestDistance && (distance <= range || range == 0.0f)) {
	bestDistance = distance;
	closest = actor;
      }
    }
  }
  return closest;
}

bool Engine::pickATile(int *x, int *y, float maxRange) {
  while (!TCODConsole::isWindowClosed()) {
    render();
    // highlight the possible range
    for (int cx=0; cx < map->width; cx++) {
      for (int cy=0; cy < map->height; cy++) {
        if ( map->isInFov(cx,cy) 
	     && ( maxRange == 0 || player->getDistance(cx,cy) <= maxRange) ) {
	  TCODColor col = TCODConsole::root->getCharBackground(cx, cy);
	  col = col * 1.2f;
	  TCODConsole::root->setCharBackground(cx,cy,col);
	}
      }
    }
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,&mouse);
    if (map->isInFov(mouse.cx,mouse.cy)
	&& (maxRange == 0 || player->getDistance(mouse.cx,mouse.cy) <= maxRange)) {
      TCODConsole::root->setCharBackground(mouse.cx,mouse.cy,TCODColor::white);
      if (mouse.lbutton_pressed) {
	*x=mouse.cx;
	*y=mouse.cy;
	return true;
      }
    }
    if (mouse.rbutton_pressed || lastKey.vk != TCODK_NONE) {
      return false;
    }
    TCODConsole::flush();
  }
  return false;
}

Actor *Engine::getActor(int x, int y) const {
  for (Actor **iterator = actors.begin();
       iterator != actors.end(); iterator++) {
    Actor *actor = *iterator;
    if (actor->x == x && actor->y == y && actor->destructible
	&& !actor->destructible->isDead()) {
      return actor;
    }
  }
  return NULL;
}

void Engine::load() {
  engine.gui->menu.clear();
  engine.gui->menu.addItem(Menu::NEW_GAME,"New Game", 0);
  if (TCODSystem::fileExists("gmtl.bin")) {
    engine.gui->menu.addItem(Menu::CONTINUE,"Continue", 0);
  }
  engine.gui->menu.addItem(Menu::EXIT, "Exit", 2);

  Menu::MenuItemCode menuItem = engine.gui->menu.pick();
  if (menuItem == Menu::EXIT || menuItem == Menu::NONE) {
    exit(0);
  } else if (menuItem == Menu::NEW_GAME) {
    engine.reinit();
    engine.init(); 
  } else {
    gmtl::Game saveGame;
    engine.reinit();
    fstream input("gmtl.bin", ios::in | ios::binary);
    if (!saveGame.ParseFromIstream(&input)) {
      cerr << "Failed to load game." << endl;
    }
    const gmtl::Game_Map gameMap = saveGame.map();
    const gmtl::Game_Actors gameActors = saveGame.actors();
    level = saveGame.level();
    map = new Map(gameMap.width(), gameMap.height());
    map->load(gameMap);
    player=new Actor(0,0,0,NULL,TCODColor::white);
    player->load(saveGame.player().actor());
    stairs = new Actor(0,0,0,NULL,TCODColor::white);
    stairs->load(saveGame.stairs().actor());
    actors.push(player);
    for (int i = 0; i < gameActors.actor_size(); i++) {
      Actor *actor = new Actor(0,0,0,NULL,TCODColor::white);
      actor->load(gameActors.actor(i));
      actors.push(actor);
    }
    gui->load(saveGame.logs());
    gameStatus = STARTUP;
  }
}

void Engine::save() {
  if (player->destructible->isDead()) {
    TCODSystem::deleteFile("gmtl.bin");
  } else {
    gmtl::Game saveGame;
    saveGame.set_level(level);
    map->save(saveGame.mutable_map());
    player->save(saveGame.mutable_player()->mutable_actor());
    stairs->save(saveGame.mutable_stairs()->mutable_actor());
    for (Actor **it = actors.begin(); it != actors.end(); it++) {
      if (*it != player && *it != stairs) {
	(*it)->save(saveGame.mutable_actors()->add_actor());
      }
    }
    gui->save(saveGame.mutable_logs());
    fstream output("gmtl.bin", ios::out | ios::trunc | ios::binary);
    if (!saveGame.SerializeToOstream(&output)) {
      cerr << "Failed to write save game." << endl;
      return;
    }
  }
}
