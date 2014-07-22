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
    x(x),y(y),ch(ch),col(col),name(name),
    blocks(true),attacker(NULL),destructible(NULL),ai(NULL),
    pickable(NULL),container(NULL){
}

Actor::~Actor() {
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

void Actor::save(gmtl::Game *saveGame) {
  gmtl::Game_Actors *gameActors = saveGame->mutable_actors();
  gmtl::Actor *actor = gameActors->add_actor();
  engine.gui->message(TCODColor::lightGrey,
		      "Saving actor x : %d", x);
  actor->set_x(x);
  printf("Saving actor y : %d", y);
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
}

void Actor::load(gmtl::Game *saveGame) {
  gmtl::Actor actor = saveGame->player().actor();
  x = actor.x();
  engine.gui->message(TCODColor::lightGrey,
			  "Loaded actor x : %d", x);
  y = actor.y();
  ch = actor.ch();
  col = TCODColor::black;
  col.setHSV(actor.color().hue(), actor.color().saturation(), actor.color().value());
  name = actor.name().c_str();
  blocks = actor.blocks();
}

float Actor::getDistance(int cx, int cy) const {
  int dx = x - cx;
  int dy = y - cy;
  return sqrtf(dx*dx+dy*dy);
}
