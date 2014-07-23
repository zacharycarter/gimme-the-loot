#include "Container.hpp"
#include "Engine.hpp"
#include "Pickable.hpp"

Pickable::~Pickable() {
}

bool Pickable::pick(Actor *owner, Actor *wearer) {
  if(wearer->container && wearer->container->add(owner)) {
    engine.actors.remove(owner);
    return true;
  }
  return false;
}

bool Pickable::use(Actor *owner, Actor *wearer) {
  if(wearer->container) {
    wearer->container->remove(owner);
    delete owner;
    return true;
  }
  return false;
}

void Pickable::drop(Actor *owner, Actor *wearer) {
  if (wearer->container) {
    wearer->container->remove(owner);
    engine.actors.push(owner);
    owner->x = wearer->x;
    owner->y = wearer->y;
    engine.gui->logEntry(TCODColor::lightGrey, "%s drops a %s.",
			wearer->name,owner->name);
  }
}

Pickable pickable *create(const gmtl::Pickable pickable) {
  Pickable *tempPickable = NULL;
  switch(pickable.type()) {
  case gmtl::PickableType::HEALER :
    if (pickable.has_healer()) tempPickable = new Healer(0);
    break;
  case gmtl::PickableType::LIGHTNING_BOLT :
    if (pickable.has_lightning_bolt()) tempPickable = new LightningBolt(0,0);
    break;
  case gmtl::PickableType::CONFUSER :
    if (pickable.has_confuser()) tempPickable = new Confuser(0,0);
    break;
  case gmtl::PickableType::FIREBALL :
    if (pickable.has_fireball()) tempPickable = new Fireball(0,0);
    break;
  }
  tempPickable->load(ai);
  return tempPickable;
}
