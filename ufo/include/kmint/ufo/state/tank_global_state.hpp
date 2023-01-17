#ifndef KMINT_UFO_TANK_GLOBAL_STATE_HPP
#define KMINT_UFO_TANK_GLOBAL_STATE_HPP

#include "kmint/ufo/tank.hpp"
#include "kmint/ufo/interface/base_state.hpp"

namespace kmint::ufo {
	class TankGlobalState : public BaseState
	{
	public:
		TankGlobalState(StateContext& stateContext, play::map_bound_actor& stateActor) : BaseState(stateContext, stateActor), tank_(dynamic_cast<tank&>(stateActor)) {}
		virtual bool onUpdateHook(delta_time dt) { return true; }
		std::string getIdentifier() override { return "globalState"; }
		virtual map::map_node& getNextNode();
	protected:
		tank& tank_;
	private:
		void onUpdate(delta_time dt) override;
		delta_time t_since_move_{};
	};
}

#endif /* KMINT_UFO_TANK_GLOBAL_STATE_HPP */