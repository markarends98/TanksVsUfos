#include "kmint/ufo/tank.hpp"
#include "kmint/graphics.hpp"
#include "kmint/ufo/state/tank/tank_state_roaming.hpp"

namespace kmint::ufo {

namespace {
graphics::image tank_image(tank_type t) {
  constexpr scalar scale = 0.35;
  switch (t) {
  case tank_type::red:
    return graphics::image{"resources/tank_red.png", scale};
  case tank_type::green:
    return graphics::image{"resources/tank_green.png", scale};
  }
  return graphics::image{"resources/tank_green.png", scale};
}


} // namespace

tank::tank(play::stage& s, map::map_graph& g, map::map_node& initial_node, tank_type t)
	: play::map_bound_actor{ initial_node }, type_{t},
	drawable_{ *this, graphics::image{tank_image(t)} },
	stage(s),
	graph(g)
{
	std::unique_ptr<TankStateRoaming> state = std::make_unique<TankStateRoaming>(this->stateContext, *this);
	this->stateContext.changeState(std::move(state));
}

void tank::act(delta_time dt) {
	stateContext.onUpdate(dt);
}

void tank::handleSaucerAttack(saucer& saucer)
{
	if(hasShield)
	{
		currentDamage += 20;
		hasShield = false;
	}else if(hasEMP)
	{
		saucer.stun(20);
		hasEMP = false;
	}else
	{
		currentDamage += 50;
	}
}
} // namespace kmint::ufo
