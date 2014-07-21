#include "Engine.hpp"
#include "MonsterDestructible.hpp"

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName) :
  Destructible(maxHp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner) {
  engine.gui->message(TCODColor::lightGrey,"%s is dead",owner->name);
  Destructible::die(owner);
}
