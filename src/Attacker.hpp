#ifndef ATTACKER_HPP
#define ATTACKER_HPP

#include "Actor.hpp"

class Attacker {
public:
  float power;
  Attacker(float power);
  void attack(Actor *owner, Actor *target);
};

#endif
