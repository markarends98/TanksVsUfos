#ifndef KMINT_UFO_TANK_STATE_REPAIRING_HPP
#define KMINT_UFO_TANK_STATE_REPAIRING_HPP

#include "kmint/ufo/andre.hpp"
#include "kmint/ufo/state/tank_global_state.hpp"
#include "kmint/ufo/tank.hpp"

namespace kmint::ufo {

	class TankStateRepairing : public TankGlobalState
	{
	public:
		TankStateRepairing(StateContext& stateContext, play::map_bound_actor& stateActor, andre& anwb) : TankGlobalState(stateContext, stateActor), anwb_(anwb) {}
		bool onUpdateHook(delta_time dt) override;
		map::map_node& getNextNode() override;
		std::string getIdentifier() override { return "tankStateRepairing"; }
		std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> current_route;
	private:
		andre& anwb_;
	};
}

#endif /* KMINT_UFO_TANK_STATE_REPAIRING_HPP */