#include "Container.hpp"

Container::Container(int size) : size(size) {
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

void Container::remove(Actor *actor) {
  inventory.remove(actor);
}
