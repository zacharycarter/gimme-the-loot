#ifndef AI_HPP
#define AI_HPP

#include "Actor.hpp"

class Ai {
public:
  virtual ~Ai();
  virtual void update(Actor *owner) = 0;
  static Ai *create(const gmtl::Ai ai);
  virtual void save(gmtl::Ai *ai);
  virtual void load(const gmtl::Ai ai);
};

inline Ai::~Ai() { } 

#endif
