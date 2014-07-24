#include "Engine.hpp"
#include "MonsterAi.hpp"
#include "Confuser.hpp"

Confuser::Confuser(int nbTurns, float range)
  : nbTurns(nbTurns),range(range) {
}

bool Confuser::use(Actor *owner, Actor *wearer) {
  engine.gui->logEntry(TCODColor::cyan, 
		      "Left-click an enemy to confuse it, \nor right-click to cancel.");
  int x,y;
  if (!engine.pickATile(&x,&y,range)) {
    return false;
  }
  Actor *actor = engine.getActor(x,y);
  if (!actor) {
    return false;
  }
  Ai *confusedAi = new ConfusedMonsterAi(nbTurns, actor->ai);
  actor->ai = confusedAi;
  engine.gui->logEntry(TCODColor::lightGreen,"The eyes of the %s look vacant, \nas they begin to stumble.",
		     actor->name);
  return Pickable::use(owner,wearer);
}

void Confuser::load(const gmtl::Pickable pickable) {
  nbTurns = pickable.confuser().nb_turns();
  range = pickable.confuser().range();
}

void Confuser::save(gmtl::Pickable *pickable) {
  pickable->set_type(gmtl::CONFUSER);
  gmtl::Confuser *confuser = pickable->mutable_confuser();
  confuser->set_nb_turns(nbTurns);
  confuser->set_range(range);
}
