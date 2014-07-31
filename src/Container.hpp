#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "libtcod.hpp"
#include "Actor.hpp"

class Container {
public:
  int size;
  int gold;
  TCODList<Actor *> inventory;
  
  Container(int size);
  ~Container();
  bool add(Actor *actor);
  void addGold(int amount);
  void remove(Actor *actor);
  void load(const gmtl::Container container);
  void save(gmtl::Container *container);
};
#endif
