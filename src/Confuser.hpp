#ifndef CONFUSER_HPP
#define CONFUSER_HPP

#include "Pickable.hpp"
#include "Actor.hpp"

class Confuser : public Pickable {
public:
  int nbTurns;
  float range;
  Confuser(int nbTurns, float range);
  bool use(Actor *owner, Actor *wearer);
};
#endif
