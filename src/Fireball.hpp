#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include "LightningBolt.hpp"
#include "Actor.hpp"

class Fireball : public LightningBolt {
public:
  Fireball(float range, float damage);
  bool use(Actor *owner, Actor *wearer);
};

#endif
