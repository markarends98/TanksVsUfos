#ifndef KMINT_UFO_TANK_STATE_FINDING_HPP
#define KMINT_UFO_TANK_STATE_FINDING_HPP

#include "kmint/ufo/state/tank_global_state.hpp"
#include "kmint/ufo/tank.hpp"

namespace kmint::ufo {

	class TankStateFinding : public TankGlobalState
	{
	public:
		TankStateFinding(StateContext& stateContext, play::map_bound_actor& stateActor, map::map_node& targetNode) : TankGlobalState(stateContext, stateActor), target_(targetNode) {}
		void onEnter() override;
		bool onUpdateHook(delta_time dt) override;
		map::map_node& getNextNode() override;
		std::string getIdentifier() override { return "tankStateFinding"; }
	private:
		std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> route_;
		map::map_node& target_;
		int path_index_ = 0;
	};
}

#endif /* KMINT_UFO_TANK_STATE_ROAMING_HPP */