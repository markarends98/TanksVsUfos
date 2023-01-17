#include "kmint/ufo/state/tank_global_state.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/node_algorithm.hpp"

namespace kmint::ufo {
	map::map_node& TankGlobalState::getNextNode()
	{
		return random_adjacent_node(this->tank_.node());
	}

	void TankGlobalState::onUpdate(const delta_time dt)
	{
		t_since_move_ += dt;
		if (to_seconds(t_since_move_) >= static_cast<float>(waiting_time(tank_.node()))) {
			if (onUpdateHook(dt)) {
				tank_.node(getNextNode());
				t_since_move_ = from_seconds(0);
			}
		}
	}
}