#include "Engine.hpp"
#include "MonsterAi.hpp"
#include "Confuser.hpp"

Confuser::Confuser(int nbTurns, float range)
  : nbTurns(nbTurns),range(range) {
}

bool Confuser::use(Actor *owner, Actor *wearer) {
  engine.gui->message(TCODColor::cyan, 
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
  engine.gui->message(TCODColor::lightGreen,"The eyes of the %s look vacant, \nas they begin to stumble.",
		     actor->name);
  return Pickable::use(owner,wearer);
}
