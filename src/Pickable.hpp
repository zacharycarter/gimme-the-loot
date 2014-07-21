#ifndef PICKABLE_HPP
#define PICKABLE_HPP

#include "Actor.hpp"

class Pickable {
public:
  virtual ~Pickable();
  bool pick(Actor *owner, Actor *wearer);
  virtual bool use(Actor *owner, Actor *wearer);
  void drop(Actor *owner, Actor *wearer);
};
#endif
