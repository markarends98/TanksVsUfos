#include "kmint/ufo/state/tank/tank_state_finding.hpp"
#include "kmint/ufo/a_star_algorithm.hpp"
#include "kmint/ufo/emp.hpp"
#include "kmint/ufo/shield.hpp"
#include "kmint/ufo/state/tank/tank_state_roaming.hpp"

namespace kmint::ufo {

	void TankStateFinding::onEnter()
	{
		route_ = aStarSearch(tank_.graph, tank_.node(), target_, { 'R', 'M', 'T', '1', '2', '3' ,'4' });
		printRoute(route_);
	}

	bool TankStateFinding::onUpdateHook(const delta_time dt)
	{
		// Check destination reached
		if (tank_.location() == target_.location())
		{
			for (auto i = tank_.begin_collision(); i != tank_.end_collision(); ++i)
			{
				auto& a = *i;
				if (typeid(a).name() == typeid(ufo::emp).name()) {
					tank_.hasEMP = true;
					a.remove();
				}
				else if(typeid(a).name() == typeid(ufo::shield).name())
				{
					tank_.hasShield = true;
					a.remove();
				}
			}
			
			clearRoute(route_);
			std::unique_ptr<TankStateRoaming> state = std::make_unique<TankStateRoaming>(this->context, tank_);
			this->context.changeState(std::move(state));
			return false;
		}
		return true;
	}

	map::map_node& TankStateFinding::getNextNode()
	{
		if (route_.first.empty() || path_index_ >= route_.first.size())
		{
			return this->tank_.node();
		}
		auto& node = *route_.first.at(path_index_);
		path_index_++;
		return node;
	}
}
