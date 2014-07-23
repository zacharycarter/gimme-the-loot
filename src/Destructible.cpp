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

void Destructible::save(gmtl::Destructible *destructible) {
  destructible->set_max_hp(maxHp);
  destructible->set_hp(hp);
  destructible->set_defense(defense);
  destructible->set_corpse_name(corpseName);
}

void Destructible::load(const gmtl::Destructible destructible) {
  maxHp = destructible.max_hp();
  hp = destructible.hp();
  defense = destructible.defense();
  corpseName = destructible.corpseName();
}

Destructible *Destructible::create(gmtl::Destructible destructible) {
  DestructibleType type=(DestructibleType)destructible.destructible_type();
  Destructible *destructible=NULL;
  switch(type) {
  case gmtl::DestructibleType::MONSTER : 
    destructible=new MonsterDestructible(0,0,NULL); 
    break;
  case gmtl::DestructibleType::PLAYER : 
    destructible=new PlayerDestructible(0,0,NULL); 
    break;
  }
  destructible->load(destructible);
  return destructible;
}
