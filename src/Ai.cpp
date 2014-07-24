#include "MonsterAi.hpp"
#include "PlayerAi.hpp"
#include "Ai.hpp"

void Ai::save(gmtl:: Ai *ai) {

}

void Ai::load(const gmtl::Ai ai) {

}

Ai *Ai::create(gmtl::Ai ai) {
  Ai *tempAi = NULL;
  switch(ai.type()) {
  case gmtl::PLAYER_AI :
    tempAi = new PlayerAi();
    break;
  case gmtl::MONSTER_AI :
    if (ai.has_monster_ai()) tempAi = new MonsterAi();
    break;
  case gmtl::CONFUSED_MONSTER_AI :
    if (ai.has_confused_monster_ai()) tempAi = new ConfusedMonsterAi(0,NULL);
    break;
  }
  tempAi->load(ai);
  return tempAi;
}
