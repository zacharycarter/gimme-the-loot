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
