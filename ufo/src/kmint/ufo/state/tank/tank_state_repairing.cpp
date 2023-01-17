#include "kmint/ufo/state/tank/tank_state_repairing.hpp"
#include "kmint/ufo/a_star_algorithm.hpp"
#include "kmint/ufo/state/tank/tank_state_roaming.hpp"

namespace kmint::ufo {
	bool TankStateRepairing::onUpdateHook(const delta_time dt)
	{
		clearRoute(current_route);
		current_route = aStarSearch(this->tank_.graph, this->tank_.node(), anwb_.node(), { 'R', 'M', 'T', '1', '2', '3' ,'4' });

		if (current_route.first.empty() || current_route.first.front()->location() == anwb_.location())
		{
			this->tank_.repair();
			std::unique_ptr<TankStateRoaming> state = std::make_unique<TankStateRoaming>(this->context, tank_);
			this->context.changeState(std::move(state));
			return false;
		}
		
		printRoute(current_route);
		return true;
	}

	map::map_node& TankStateRepairing::getNextNode()
	{
		return *current_route.first.front();
	}
}
