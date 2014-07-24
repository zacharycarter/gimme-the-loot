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

void Healer::load(const gmtl::Pickable pickable) {
  amount = pickable.healer().amount();
}

void Healer::save(gmtl::Pickable *pickable) {
  pickable->set_type(gmtl::HEALER);
  gmtl::Healer *healer = pickable->mutable_healer();
  healer->set_amount(amount);
}
