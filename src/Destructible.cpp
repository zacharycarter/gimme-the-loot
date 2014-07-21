#include "Destructible.hpp"
#include "Engine.hpp"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) :
  maxHp(maxHp),hp(maxHp),defense(defense),corpseName(corpseName) {
}

Destructible::~Destructible() {
}

float Destructible::takeDamage(Actor *owner, float damage) {
  damage -= defense;
  if (damage > 0) {
    hp -= damage;
    if(hp <= 0) {
      die(owner);
    }
  } else {
    damage = 0;
  }
  return damage;
}

float Destructible::heal(float amount) {
  hp += amount;
  if(hp > maxHp) {
    amount -= hp-maxHp;
    hp = maxHp;
  }
  return amount;
}

void Destructible::die(Actor *owner) {
  owner->ch='%';
  owner->col=TCODColor::darkRed;
  owner->name=corpseName;
  owner->blocks=false;
  engine.sendToBack(owner);
}
