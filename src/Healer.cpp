#include "Destructible.hpp"
#include "Healer.hpp"

Healer::Healer(float amount) : amount(amount) {
}

bool Healer::use(Actor *owner, Actor *wearer) {
  if (wearer->destructible) {
    float amountHealed = wearer->destructible->heal(amount);
    if (amountHealed > 0) {
      return Pickable::use(owner, wearer);
    }
  }
  return false;
}
