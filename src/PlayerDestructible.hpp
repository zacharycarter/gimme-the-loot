#ifndef PLAYER_DESTRUCTIBLE_HPP
#define PLAYER_DESTRUCTIBLE_HPP

#include "Destructible.hpp"

class PlayerDestructible : public Destructible {
public:
  PlayerDestructible(float maxHp, float defense, const char *corpseName);
  void die(Actor *owner);
  void save(gmtl::Destructible *destructible);
};

#endif
