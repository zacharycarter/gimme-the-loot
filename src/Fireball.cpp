#include "Destructible.hpp"
#include "Engine.hpp"
#include "Fireball.hpp"

Fireball::Fireball(float range, float damage)
  : LightningBolt(range,damage) {
}

bool Fireball::use(Actor *owner, Actor *wearer) {
  engine.gui->message(TCODColor::cyan,
		      "Left-click a target a tile for the fireball, \nor right-click to cancel.");
  int x,y;
  if (!engine.pickATile(&x,&y)) {
    return false;
  }
  engine.gui->message(TCODColor::orange, 
		      "The fireball explodes, burning everything within %g tiles!",range);
  for (Actor **iterator = engine.actors.begin();
       iterator != engine.actors.end(); iterator++) {
    Actor *actor = *iterator;
    if (actor->destructible && !actor->destructible->isDead()
	&& actor->getDistance(x,y) <= range) {
      engine.gui->message(TCODColor::orange,
			  "The %s gets burned for %g hit points.",actor->name,damage);
      actor->destructible->takeDamage(actor,damage);
    }
  }
  return Pickable::use(owner,wearer);
}
