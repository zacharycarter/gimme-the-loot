#include "Engine.hpp"
#include "MonsterDestructible.hpp"

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName) :
  Destructible(maxHp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner) {
  engine.gui->logEntry(TCODColor::lightGrey,"%s is dead",owner->name);
  Destructible::die(owner);
}

void MonsterDestructible::save(gmtl::Destructible *destructible) {
  destructible->set_destructible_type(gmtl::DestructibleType::MONSTER);
  Destructible::save(destructible);
}
