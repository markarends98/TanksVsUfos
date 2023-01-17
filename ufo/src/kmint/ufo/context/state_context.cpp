#include "kmint/ufo/context/state_context.hpp"

namespace kmint::ufo {
	void StateContext::onUpdate(const delta_time dt) const
	{
		this->current_state_->onUpdate(dt);
	}

	void StateContext::changeState(std::unique_ptr<BaseState> newState)
	{
		if (this->current_state_ != nullptr) {
			this->current_state_->onExit();
		}
		if (newState != nullptr) {
			this->current_state_ = std::move(newState);
			this->current_state_->onEnter();
			active_state_ = this->current_state_->getIdentifier();
		}
	}
}