#ifndef HEALER_HPP
#define HEALER_HPP

#include "Actor.hpp"
#include "Pickable.hpp"

class Healer : public Pickable {
public:
  float amount;
  
  Healer(float amount);
  bool use(Actor *owner, Actor *wearer);
  void load(const gmtl::Pickable pickable);
  void save(gmtl::Pickable *pickable);
};
#endif
