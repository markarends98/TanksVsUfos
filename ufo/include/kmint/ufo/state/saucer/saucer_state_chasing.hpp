#ifndef KMINT_UFO_SAUCER_STATE_CHASING_HPP
#define KMINT_UFO_SAUCER_STATE_CHASING_HPP

#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/state/saucer_global_state.hpp"

namespace kmint::ufo {
	class SaucerStateChasing : public SaucerGlobalState
	{
	public:
		SaucerStateChasing(StateContext& stateContext, play::actor& stateActor, play::actor& target) : SaucerGlobalState(stateContext, stateActor), target_(dynamic_cast<ForceDrivenEntity&>(target)) {}
		void onUpdateHook(delta_time dt) override;
		std::string getIdentifier() override { return "saucerStateChasing"; }
	private:
		ForceDrivenEntity& target_;
	};
}

#endif /* KMINT_UFO_SAUCER_STATE_CHASING_HPP */