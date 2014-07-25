#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "libtcod.hpp"
#include "gmtl.pb.h"

class Attacker;
class Destructible;
class Ai;
class Pickable;
class Container;

class Actor {
public :
  int x,y; // position on map
  int ch; // ascii code
  TCODColor col; // color
  char *name;
  bool blocks;
  bool fovOnly;
  Attacker *attacker;
  Destructible *destructible;
  Ai *ai;
  Pickable *pickable;
  Container *container;
  Actor(int x, int y, int ch, const char *name, const TCODColor &col);
  ~Actor();
  void update();
  void render() const;
  void save(gmtl::Actor *actor);
  void load(const gmtl::Actor actor);
  float getDistance(int cx, int cy) const;
};

#endif
