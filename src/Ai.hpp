#ifndef AI_HPP
#define AI_HPP

class Actor;

class Ai {
public:
  virtual ~Ai();
  virtual void update(Actor *owner) = 0;
  static Ai *create(gmtl::Ai ai);
};

inline Ai::~Ai() { } 

#endif
