#include <math.h>

#include "Attacker.hpp"
#include "Destructible.hpp"
#include "Engine.hpp"
#include "MonsterAi.hpp"

static const int TRACKING_TURNS=3;

MonsterAi::MonsterAi() : moveCount(0) {
}

MonsterAi::~MonsterAi() {
}

void MonsterAi::update(Actor *owner) {
  if (owner->destructible && owner->destructible->isDead()) {
    return;
  }
  if (engine.map->isInFov(owner->x, owner->y)) {
    moveCount = TRACKING_TURNS;
  } else {
    moveCount--;
  }
  if (moveCount > 0) {
    moveOrAttack(owner, engine.player->x, engine.player->y);
  }
}

void MonsterAi::moveOrAttack(Actor *owner, int targetx, int targety) {
  int dx = targetx - owner->x;
  int dy = targety - owner->y;
  int stepdx = (dx > 0 ? 1:-1);
  int stepdy = (dy > 0 ? 1:-1);
  float distance = sqrtf(dx*dx+dy*dy);
  if (distance >= 2) {
    dx = (int)(round(dx/distance));
    dy = (int)(round(dy/distance));
    if (engine.map->canWalk(owner->x + dx, owner->y + dy)) {
      owner->x += dx;
      owner->y += dy;
    } else if (engine.map->canWalk(owner->x + stepdx, owner->y)) {
      owner->x += stepdx;
    } else if (engine.map->canWalk(owner->x, owner->y + stepdy)) {
      owner->y += stepdy;
    }
  } else if (owner->attacker) {
    owner->attacker->attack(owner,engine.player);
  }
}

void MonsterAi::load(const gmtl::Ai ai) {
  moveCount = ai.monster_ai.move_count;
}

void MonsterAi::save(gmtl::Ai *ai) {
  ai->set_type(gmtl::AiType::MONSTER_AI);
  ai->set_move_count(moveCount);
}

ConfusedMonsterAi::ConfusedMonsterAi(int nbTurns, Ai *oldAi)
  : nbTurns(nbTurns),oldAi(oldAi) {
}

void ConfusedMonsterAi::update(Actor *owner) {
  if (owner->destructible && owner->destructible->isDead()) {
    return;
  }
  TCODRandom *rng = TCODRandom::getInstance();
  int dx = rng->getInt(-1,1);
  int dy = rng->getInt(-1,1);
  if (dx != 0 || dy != 0) {
    int destx = owner->x + dx;
    int desty = owner->y + dy;
    if (engine.map->canWalk(destx, desty)) {
	owner->x = destx;
	owner->y = desty;
    } else {
      Actor *actor = engine.getActor(destx, desty);
      if (actor) {
	owner->attacker->attack(owner,actor);
      }
    }
  }
  nbTurns--;
  if (nbTurns == 0) {
    owner->ai = oldAi;
    delete this;
  }
}

void ConfusedMonsterAi::load(gmtl::Ai ai) {
  nbTurns = ai.confused_monster_ai().nbTurns();
  oldAi = Ai::create(ai.confused_monster_ai().old_ai();
}

void ConfusedMonsterAi::save(gmtl::Ai *ai) {
  ai->set_type(gmtl::AiType::CONFUSED_MONSTER_AI);
  gmtl::ConfusedMonsterAi *confusedMonsterAi = ai->mutable_confused_monster_ai();
  confusedMonsterAi->set_old_ai(Ai::save(mutable_old_ai());
}
