#ifndef KMINT_UFO_STATE_CONTEXT_HPP
#define KMINT_UFO_STATE_CONTEXT_HPP

#include <memory>
#include "kmint/ufo/interface/base_state.hpp"
#include "kmint/primitives.hpp"

namespace kmint::ufo {
	class BaseState;

	class StateContext
	{
	private:
		std::unique_ptr<BaseState> current_state_;
		std::string active_state_;
	public:
		void onUpdate(delta_time dt) const;
		void changeState(std::unique_ptr<BaseState> newState);
		std::string getCurrentState() const { return current_state_->getIdentifier(); }
	};
}

#endif /* KMINT_UFO_STATE_CONTEXT_HPP */