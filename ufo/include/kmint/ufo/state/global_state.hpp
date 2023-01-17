#ifndef KMINT_UFO_GLOBAL_STATE_HPP
#define KMINT_UFO_GLOBAL_STATE_HPP

#include "kmint/ufo/interface/base_state.hpp"

namespace kmint::ufo {
	class GlobalState : public BaseState
	{
	public:
		GlobalState(StateContext& stateContext, play::map_bound_actor& stateActor, map::map_graph& mapGraph) : BaseState(stateContext, stateActor), actor(dynamic_cast<play::map_bound_actor&>(stateActor)), map_graph(mapGraph) {}
		virtual void onUpdateHook() = 0;
		std::string getIdentifier() override { return "globalState"; }

		play::map_bound_actor& actor;
		map::map_graph& map_graph;
	private:
		void onUpdate(delta_time dt) override;
		delta_time t_since_move_{};
		// std::vector<map::map_node*> path;
		// int path_index;
		// int health;
	};
}

#endif /* KMINT_UFO_GLOBAL_STATE_HPP */