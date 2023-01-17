#ifndef KMINT_UFO_SAUCER_STATE_ATTACKING_HPP
#define KMINT_UFO_SAUCER_STATE_ATTACKING_HPP

#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/tank.hpp"
#include "kmint/ufo/state/saucer_global_state.hpp"

namespace kmint::ufo {
	class SaucerStateAttacking : public SaucerGlobalState
	{
	public:
		SaucerStateAttacking(StateContext& stateContext, play::actor& stateActor, play::actor& target) : SaucerGlobalState(stateContext, stateActor), target_(dynamic_cast<tank&>(target)) {}
		void onUpdateHook(delta_time dt) override;
		std::string getIdentifier() override { return "saucerStateAttacking"; }
	private:
		tank& target_;
	};
}

#endif /* KMINT_UFO_SAUCER_STATE_ATTACKING_HPP */