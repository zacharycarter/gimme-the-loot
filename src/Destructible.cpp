#include "Engine.hpp"
#include "MonsterDestructible.hpp"
#include "PlayerDestructible.hpp"
#include "Destructible.hpp"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) :
  maxHp(maxHp),hp(maxHp),defense(defense) {
  if(corpseName) this->corpseName = strdup(corpseName);
}

Destructible::~Destructible() {
  if(corpseName) free(corpseName);
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
  if(corpseName) owner->name=strdup(corpseName);
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
  if (destructible.corpse_name().size() > 0) {
    corpseName = strdup(destructible.corpse_name().c_str());
  }
}

Destructible *Destructible::create(gmtl::Destructible destructible) {
  Destructible *tempDestructible = NULL;
  switch(destructible.destructible_type()) {
  case gmtl::MONSTER : 
    tempDestructible = new MonsterDestructible(0,0,NULL); 
    break;
  case gmtl::PLAYER : 
    tempDestructible = new PlayerDestructible(0,0,NULL); 
    break;
  }
  tempDestructible->load(destructible);
  return tempDestructible;
}
