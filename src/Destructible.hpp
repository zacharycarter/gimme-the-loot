#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

#include "Actor.hpp"

class Destructible {
public:
  float maxHp;
  float hp;
  float defense;
  char *corpseName;

  Destructible(float maxHp, float defense, const char* corpseName);
  virtual ~Destructible();
  inline bool isDead() { return hp <= 0; }
  float takeDamage(Actor *owner, float damage);
  float heal(float amount);
  virtual void die(Actor *owner);
  virtual void save(gmtl::Destructible *destructible);
  virtual void load(const gmtl::Destructible destructible);
  static Destructible *create(gmtl::Destructible destructible);
};

#endif
