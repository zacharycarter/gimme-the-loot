#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "libtcod.hpp"
#include "Actor.hpp"

class Container {
public:
  int size;
  TCODList<Actor *> inventory;
  
  Container(int size);
  ~Container();
  bool add(Actor *actor);
  void remove(Actor *actor);
  void load(const gmtl::Container container);
  void save(gmtl::Container *container);
};
#endif
