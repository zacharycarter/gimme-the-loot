#include "Actor.hpp"
#include "Engine.hpp"
#include "PlayerDestructible.hpp"

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) :
  Destructible(maxHp,defense,corpseName) {
}

void PlayerDestructible::die(Actor *owner) {
  engine.gui->message(TCODColor::red,"You died!");
  Destructible::die(owner);
  engine.gameStatus=Engine::DEFEAT;
}
