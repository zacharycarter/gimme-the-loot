#ifndef PLAYER_AI_HPP
#define PLAYER_AI_HPP

#include "Ai.hpp"
#include "Actor.hpp"

class PlayerAi : public Ai {
public:
  ~PlayerAi();
  void update(Actor *owner);
protected:
  bool moveOrAttack(Actor *owner, int targetx, int targety);
  void handleActionKey(Actor *owner, int ascii);
  Actor *choseFromInventory(Actor *owner);
  void load(const gmtl::Ai ai);
  void save(gmtl::Ai *ai);
};

#endif
