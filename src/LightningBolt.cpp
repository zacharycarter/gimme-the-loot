#include "Destructible.hpp"
#include "Engine.hpp"
#include "LightningBolt.hpp"

LightningBolt::LightningBolt(float range, float damage) : 
  range(range),damage(damage) {
}

bool LightningBolt::use(Actor *owner, Actor *wearer) {
	Actor *closestMonster=engine.getClosestMonster(wearer->x,wearer->y,range);
	if (! closestMonster ) {
		engine.gui->logEntry(TCODColor::lightGrey,"No enemy is close enough to strike.");
		return false;
	}
	// hit closest monster for <damage> hit points
	engine.gui->logEntry(TCODColor::lightBlue,
		"A lighting bolt strikes the %s with a loud thunder!\n"
		"The damage is %g hit points.",
		closestMonster->name,damage);
	closestMonster->destructible->takeDamage(closestMonster,damage);
	return Pickable::use(owner,wearer);
}

void LightningBolt::load(const gmtl::Pickable pickable) {
  range = pickable.lightning_bolt().range();
  damage = pickable.lightning_bolt().damage();
}

void LightningBolt::save(gmtl::Pickable *pickable) {
  pickable->set_type(gmtl::LIGHTNING_BOLT);
  gmtl::LightningBolt *lightningBolt = pickable->mutable_lightning_bolt();
  lightningBolt->set_range(range);
  lightningBolt->set_damage(damage);
}
