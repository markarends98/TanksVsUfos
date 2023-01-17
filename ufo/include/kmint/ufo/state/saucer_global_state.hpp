#ifndef KMINT_UFO_SAUCER_GLOBAL_STATE_HPP
#define KMINT_UFO_SAUCER_GLOBAL_STATE_HPP

#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/interface/base_state.hpp"

namespace kmint::ufo {
	class SaucerGlobalState : public BaseState
	{
	public:
		SaucerGlobalState(StateContext& stateContext, play::actor& stateActor) : BaseState(stateContext, stateActor), saucer_(dynamic_cast<saucer&>(stateActor)){}
		virtual void onUpdateHook(delta_time dt) {};
		std::string getIdentifier() override { return "saucerGlobalState"; }
	private:
		void onUpdate(delta_time dt) override;
	protected:
		saucer& saucer_;
	};
}

#endif /* KMINT_UFO_SAUCER_GLOBAL_STATE_HPP */