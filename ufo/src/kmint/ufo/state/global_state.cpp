#include "kmint/ufo/state/global_state.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/node_algorithm.hpp"

namespace kmint::ufo {
	void GlobalState::onUpdate(delta_time dt)
	{
		t_since_move_ += dt;
		if (to_seconds(t_since_move_) >= waiting_time(actor.node())) {
			onUpdateHook();
			t_since_move_ = from_seconds(0);
		}
	}
}