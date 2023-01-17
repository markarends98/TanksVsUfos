#include "kmint/ufo/state/tank/tank_state_fleeing.hpp"
#include "kmint/ufo/a_star_algorithm.hpp"
#include "kmint/ufo/state/tank/tank_state_roaming.hpp"

namespace kmint::ufo {
	bool TankStateFleeing::onUpdateHook(const delta_time dt)
	{
		if(!sees(tank_, pursuer_))
		{
			std::unique_ptr<TankStateRoaming> state = std::make_unique<TankStateRoaming>(this->context, tank_);
			this->context.changeState(std::move(state));
			return false;
		}
		return true;
	}

	map::map_node& TankStateFleeing::getNextNode()
	{
		map::map_node* furthest_node = &tank_.node();
		float furthest = 0.0f;
		for (auto it = tank_.node().begin(); it != tank_.node().end(); ++it)
		{
			const float dist = distance(it->to().location(), pursuer_.location());
			if(dist > furthest)
			{
				furthest = dist;
				furthest_node = &it->to();
			}
		}
		return *furthest_node;
	}
}
