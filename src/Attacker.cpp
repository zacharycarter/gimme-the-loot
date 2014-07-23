#include "Destructible.hpp"
#include "Engine.hpp"
#include "Attacker.hpp"

Attacker::Attacker(float power) : power(power) {
}

void Attacker::attack(Actor *owner, Actor *target) {
  if (target->destructible && !target->destructible->isDead()) {
    if (power - target->destructible->defense > 0) {
      engine.gui->logEntry(owner==engine.player ? TCODColor::red : TCODColor::lightGrey,
			  "%s attacks %s for %g hit points.", owner->name, target->name,
			  power - target->destructible->defense);    
    } else {
      engine.gui->logEntry(TCODColor::lightGrey,
			  "%s attacks %s but it has no effect!", owner->name, target->name);
    }
    target->destructible->takeDamage(target, power);
  } else {
    engine.gui->logEntry(TCODColor::lightGrey,
			"%s attacks %s in vain.",owner->name,target->name);
  }
}

void Attacker::save(gmtl::Attacker *attacker) {
  attacker->set_power(power);
}

void Attacker::load(const gmtl::Attacker attacker) {
  power = attacker.power();
}
