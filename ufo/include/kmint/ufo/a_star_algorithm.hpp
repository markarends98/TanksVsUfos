#ifndef KMINT_UFO_A_STAR_ALGORITHM_HPP
#define KMINT_UFO_A_STAR_ALGORITHM_HPP

#include "kmint/map/map.hpp"

namespace kmint {
	namespace ufo {
		std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> aStarSearch(map::map_graph& map, map::map_node& source, map::map_node& target, const std::vector<char>& walkableLayers = {});
		std::vector<map::map_node*> retracePath(const map::map_node& source, map::map_node& target);
		float getDistance(const map::map_node& source, const map::map_node& target);
		float getDistance2(map::map_node* source, map::map_node* target);
		bool isValid(const map::map_graph& map, float x, float y, const std::vector<char>& walkableLayers);
		bool isDestination(const map::map_node& source, const int x, const int y);
		void printRoute(std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> route);
		void clearRoute(std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> route);
	}
}

#endif /* KMINT_UFO_A_STAR_ALGORITHM_HPP */