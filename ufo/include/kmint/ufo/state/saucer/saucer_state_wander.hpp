#ifndef KMINT_UFO_SAUCER_STATE_WANDER_HPP
#define KMINT_UFO_SAUCER_STATE_WANDER_HPP

#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/state/saucer_global_state.hpp"

namespace kmint::ufo {
	class SaucerStateWander : public SaucerGlobalState
	{
	public:
		SaucerStateWander(StateContext& stateContext, play::actor& stateActor) : SaucerGlobalState(stateContext, stateActor){}
		void onUpdateHook(delta_time dt) override;
		std::string getIdentifier() override { return "saucerStateWander"; }
	};
}

#endif /* KMINT_UFO_SAUCER_STATE_WANDER_HPP */