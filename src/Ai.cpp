#include "Ai.hpp"

Ai *Ai::create(gmtl::Ai ai) {
  AiType type = (AiType)ai.type();
  Ai *tempAi = NULL;
  switch(type) {
  case gmtl::AiType::PLAYER_AI :
    tempAi = new PlayerAi();
    break;
  case gmtl::AiType::MONSTER_AI :
    if (ai.has_monster_ai()) tempAi = new MonsterAi();
    break;
  case gmtl::AiType::CONFUSED_MONSTER_AI :
    if (ai.has_confused_monster_ai()) tempAi = new ConfusedMonsterAi(0,NULL);
    break;
  }
  tempAi->load(ai);
  return tempAi;
}
