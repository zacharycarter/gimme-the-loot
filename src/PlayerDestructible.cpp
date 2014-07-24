#include "Engine.hpp"
#include "PlayerDestructible.hpp"

PlayerDestructible::PlayerDestructible(float maxHp, float defense, const char *corpseName) :
  Destructible(maxHp,defense,corpseName) {
}

void PlayerDestructible::die(Actor *owner) {
  engine.gui->logEntry(TCODColor::red,"You died!");
  Destructible::die(owner);
  engine.gameStatus=Engine::DEFEAT;
}

void PlayerDestructible::save(gmtl::Destructible *destructible) {
  destructible->set_destructible_type(gmtl::PLAYER);
  Destructible::save(destructible);
}
