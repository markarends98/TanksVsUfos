#include "kmint/ufo/state/andre/andre_state_roaming.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/node_algorithm.hpp"
#include "kmint/ufo/a_star_algorithm.hpp"

namespace kmint::ufo {
	void AndreStateRoaming::onUpdateHook()
	{
		// Calculate route (if neccessary)
		if (shouldFindRoute)
		{
			currentRoute = aStarSearch(this->map_graph, actor.node(), find_node_of_kind(this->map_graph, '0' + targetStation), { 'R', 'M', 'T', '1', '2', '3' ,'4' });
			shouldFindRoute = false;

			// Render path colors
			for (auto node : currentRoute.second)
			{
				node->tag(graph::node_tag::visited);
			}
			
			for (auto node : currentRoute.first)
			{
				node->tag(graph::node_tag::path);
			}
		}
		
		// Move
		if (path_index < currentRoute.first.size()) {
			actor.node().tag(graph::node_tag::normal);
			map::map_node& node = *currentRoute.first.at(path_index);
			actor.node(node);
			path_index++;
		}

		// Check destination reached
		if(actor.location() == find_node_of_kind(this->map_graph, '0' + targetStation).location())
		{
			for (auto node : currentRoute.second)
			{
				node->tag(graph::node_tag::normal);
			}
			
			path_index = 0;
			shouldFindRoute = true;
			currentRoute.first.clear();
			currentRoute.second.clear();

			switch (targetStation)
			{
				case 1:
					targetStation = 2;
					break;
				case 2:
					targetStation = 3;
					break;
				case 3:
					targetStation = 4;
					break;
				default:
					targetStation = 1;
					break;
			}
		}
	}
}