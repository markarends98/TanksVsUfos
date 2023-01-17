#ifndef KMINT_UFO_ANDRE_STATE_ROAMING_HPP
#define KMINT_UFO_ANDRE_STATE_ROAMING_HPP

#include "kmint/ufo/state/global_state.hpp"

namespace kmint::ufo {
	class AndreStateRoaming : public GlobalState
	{
	public:
		AndreStateRoaming(StateContext& stateContext, play::map_bound_actor& stateActor, map::map_graph& mapGraph) : GlobalState(stateContext, stateActor, mapGraph) {}
		void onUpdateHook() override;
		std::string getIdentifier() override { return "andreStateRoaming"; }
	private:
		int targetStation = 1;
		int path_index = 0;
		bool shouldFindRoute = true;
		std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> currentRoute;
	};
}

#endif /* KMINT_UFO_TANK_STATE_ROAMING_HPP */