#include <math.h>
#include <stdio.h>
#include "Ai.hpp"
#include "Attacker.hpp"
#include "Container.hpp"
#include "Destructible.hpp"
#include "Pickable.hpp"
#include "Map.hpp"
#include "Engine.hpp"
#include "Actor.hpp"

using namespace std;

Actor::Actor(int x, int y, int ch, const char *name, 
    const TCODColor &col) :
  x(x),y(y),ch(ch),col(col),
  blocks(true),attacker(NULL),destructible(NULL),ai(NULL),
  pickable(NULL),container(NULL) {
  if(name) this->name = strdup(name);
}

Actor::~Actor() {
  if (name) free(name);
  if (attacker) delete attacker;
  if (destructible) delete destructible;
  if (ai) delete ai;
  if (pickable) delete pickable;
  if (container) delete container;
}
 
void Actor::render() const {
    TCODConsole::root->setChar(x,y,ch);
    TCODConsole::root->setCharForeground(x,y,col);
}

void Actor::update() {
	if ( ai ) ai->update(this);
}

void Actor::save(gmtl::Actor *actor) {
  actor->set_x(x);
  actor->set_y(y);
  actor->set_ch(ch);
  
  gmtl::Color *color = actor->mutable_color();
  float h,s,v;
  col.getHSV(&h,&s,&v);
  color->set_hue(h);
  color->set_saturation(s);
  color->set_value(v);
  
  actor->set_name(name);
  actor->set_blocks(blocks);

  if (attacker) attacker->save(actor->mutable_attacker());
  if (destructible) destructible->save(actor->mutable_destructible());
  if (ai) ai->save(actor->mutable_ai());
  if (pickable) pickable->save(actor->mutable_pickable());
  if (container) container->save(actor->mutable_container());
}

void Actor::load(const gmtl::Actor actor) {
  const gmtl::Color color = actor.color();
  x = actor.x();
  y = actor.y(); 
  ch = actor.ch();
  col.setHSV(color.hue(), color.saturation(), color.value());
  if(actor.name().size() > 0) name = strdup(actor.name().c_str());
  blocks = actor.blocks();

  if (actor.has_attacker()) {
    attacker = new Attacker(0.0f);
    attacker->load(actor.attacker());
  }

  if (actor.has_destructible()) {
    destructible = Destructible::create(actor.destructible());
  }

  if (actor.has_ai()) {
    ai = Ai::create(actor.ai());
  }

  if (actor.has_pickable()) {
    pickable = Pickable::create(actor.pickable());
  }

  if (actor.has_container()) {
    container = new Container(0);
    container->load(actor.container());
  }
}

float Actor::getDistance(int cx, int cy) const {
  int dx = x - cx;
  int dy = y - cy;
  return sqrtf(dx*dx+dy*dy);
}
