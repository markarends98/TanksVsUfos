#ifndef KMINT_UFO_TANK_STATE_ROAMING_HPP
#define KMINT_UFO_TANK_STATE_ROAMING_HPP

#include "kmint/ufo/a_star_algorithm.hpp"
#include "kmint/ufo/state/tank_global_state.hpp"
#include "kmint/ufo/tank.hpp"
#include "kmint/ufo/node_algorithm.hpp"

namespace kmint::ufo {

	class TankStateRoaming : public TankGlobalState
	{
	public:
		TankStateRoaming(StateContext& stateContext, play::map_bound_actor& stateActor) : TankGlobalState(stateContext, stateActor) {}
		bool onUpdateHook(delta_time dt) override;
		std::string getIdentifier() override { return "tankStateRoaming"; }

		template<typename T>
		map::map_node& getClosestObject() const;
	};

	template <typename T>
	map::map_node& TankStateRoaming::getClosestObject() const
	{
		std::vector<std::pair<map::map_node*, float>> nodes;
		for (auto item : this->tank_.stage.getActors<T>())
		{
			map::map_node* source = &find_without_const_closest_node_to(tank_.graph, this->tank_.location());
			map::map_node* target = &find_without_const_closest_node_to(tank_.graph, item->get()->location());

			nodes.push_back(std::make_pair(target, getDistance2(source, target)));
		}

		const auto result = std::min_element(nodes.begin(), nodes.end(),
			[](const std::pair<map::map_node*, float>& a, const std::pair<map::map_node*, float>& b)
			{
				return a.second < b.second;
			});
		return *result->first;
	}
}

#endif /* KMINT_UFO_TANK_STATE_ROAMING_HPP */