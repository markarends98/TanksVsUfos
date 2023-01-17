#ifndef KMINT_UFO_TANK_STATE_FLEEING_HPP
#define KMINT_UFO_TANK_STATE_FLEEING_HPP

#include "kmint/ufo/state/tank_global_state.hpp"
#include "kmint/ufo/tank.hpp"

namespace kmint::ufo {

	class TankStateFleeing : public TankGlobalState
	{
	public:
		TankStateFleeing(StateContext& stateContext, play::map_bound_actor& stateActor, play::actor& pursuer) : TankGlobalState(stateContext, stateActor), pursuer_(pursuer) {}
		map::map_node& getNextNode() override;
		bool onUpdateHook(delta_time dt) override;
		std::string getIdentifier() override { return "tankStateFleeing"; }
	private:
		play::actor& pursuer_;
	};
}

#endif /* KMINT_UFO_TANK_STATE_ROAMING_HPP */