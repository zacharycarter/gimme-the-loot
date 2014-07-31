#include "Container.hpp"

Container::Container(int size) : size(size),gold(0) {
}

Container::~Container() {
  inventory.clearAndDelete();
}

bool Container::add(Actor *actor) {
  if(size > 0 && inventory.size() >= size) {
    return false;
  }
  inventory.push(actor);
  return true;
}

void Container::addGold(int amount) {
  this->gold += amount;
}

void Container::remove(Actor *actor) {
  inventory.remove(actor);
}

void Container::load(const gmtl::Container container) {
  size = container.size();
  gold = container.gold();
  for (int i = 0; i < container.actor_size(); i++) {
    Actor *actor = new Actor(0,0,0,NULL,TCODColor::white);
    actor->load(container.actor(i));
    inventory.push(actor);
  }
}

void Container::save(gmtl::Container *container) {
  container->set_size(size);
  container->set_gold(gold);
  container->set_inventory_size(inventory.size());
  for (Actor **it = inventory.begin(); it != inventory.end(); it++) {
    (*it)->save(container->add_actor());
  }
}
