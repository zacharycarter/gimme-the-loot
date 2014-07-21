#ifndef MONSTER_DESTRUCTIBLE_H
#define MONSTER_DESTRUCTIBLE_H

#include "Actor.hpp"
#include "Destructible.hpp"

class MonsterDestructible : public Destructible {
public:
  MonsterDestructible(float maxHp, float defense, const char *corpseName);
  void die(Actor *owner);
};

#endif
