#ifndef KMINT_UFO_BASE_STATE_HPP
#define KMINT_UFO_BASE_STATE_HPP

#include "kmint/primitives.hpp"
#include "kmint/play.hpp"

namespace kmint::ufo {
	class StateContext;
	class BaseState
	{
	protected:
		StateContext& context;
		play::actor& actor;
		delta_time t_passed_{};
	public:
		BaseState(StateContext& stateContext, play::actor& playActor) : context(stateContext), actor(playActor) { };
		virtual ~BaseState() = default;
		virtual void onEnter() {};
		virtual void onUpdate(delta_time dt) = 0;
		virtual void onExit() {};
		virtual std::string getIdentifier() = 0;
	};
}

#endif /* KMINT_UFO_BASE_STATE_HPP */