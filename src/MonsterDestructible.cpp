#include "Container.hpp"
#include "Engine.hpp"
#include "MonsterDestructible.hpp"

MonsterDestructible::MonsterDestructible(float maxHp, float defense, const char *corpseName) :
  Destructible(maxHp,defense,corpseName) {
}

void MonsterDestructible::die(Actor *owner) {
  engine.player->container->addGold(owner->container->gold);
  engine.gui->logEntry(TCODColor::lightGrey,"%s is dead.",owner->name);
  engine.gui->logEntry(TCODColor::gold, "you retrieve %i gold from the %s's corpse.",
		       owner->container->gold, owner->name);
  Destructible::die(owner);
}

void MonsterDestructible::save(gmtl::Destructible *destructible) {
  destructible->set_destructible_type(gmtl::MONSTER);
  Destructible::save(destructible);
}
