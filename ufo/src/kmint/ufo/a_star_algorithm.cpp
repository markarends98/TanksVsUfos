#include "kmint/ufo/a_star_algorithm.hpp"

#include <iostream>
#include <stack>
#include <vector>

namespace kmint {
	namespace ufo {

		// Approximation Heuristics - Manhattan Distance
		// G cost = distance from start node
		// H cost (heuristic) = distance from end node
		// F cost = G cost + H cost
		std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> aStarSearch(map::map_graph& map, map::map_node& source, map::map_node& target, const std::vector<char>& walkableLayers)
		{
			std::vector<map::map_node*> found_path;
			std::vector<map::map_node*> path_nodes;

			if (!isValid(map, target.location().x(), target.location().y(), walkableLayers)) {
				return {};
			}

			if (isDestination(source, target.location().x(), target.location().y())) {
				return {};
			}

			//// Closed / open list
			std::vector<map::map_node*> open;
			std::vector<map::map_node*> closed;
			open.push_back(&source);

			while (!open.empty())
			{
				map::map_node* current_node = open.at(0);

				for (int i = 1; i < open.size(); i++)
				{
					map::map_node& other_node = *open.at(i);
					if (other_node.node_info().f_cost() < current_node->node_info().f_cost() || other_node.node_info().f_cost() == current_node->node_info().f_cost())
						if (other_node.node_info().h_cost < current_node->node_info().h_cost) {
							{
								current_node = open.at(i);
							}
						}
				}

				// All visited nodes
				path_nodes.push_back(current_node);
				
				open.erase(std::find(open.begin(), open.end(), current_node));
				closed.push_back(current_node);

				// Found path
				if (current_node->node_id() == target.node_id())
				{
					found_path = retracePath(source, target);
					break;
				}

				for (auto it = current_node->begin(); it != current_node->end(); ++it) {
					map::map_node* neighbor = &it->to();

					if (std::find(walkableLayers.begin(), walkableLayers.end(), neighbor->node_info().kind) == walkableLayers.end() || std::find(closed.begin(), closed.end(), neighbor) != closed.end()) {
						continue;
					}

					const float new_movement_cost_to_neighbor = current_node->node_info().g_cost + getDistance(*current_node, *neighbor);
					if (new_movement_cost_to_neighbor < neighbor->node_info().g_cost || !std::count(open.begin(), open.end(), neighbor))
					{
						neighbor->node_info().g_cost = new_movement_cost_to_neighbor;
						neighbor->node_info().h_cost = getDistance(*neighbor, target);
						neighbor->node_info().parent = current_node;
						neighbor->node_info().weight = it->weight();

						if (std::find(open.begin(), open.end(), neighbor) == open.end()) {
							// All visited nodes
							path_nodes.push_back(neighbor);
							
							open.push_back(neighbor);
						}
					}
				}
			}

			return std::make_pair(found_path, path_nodes);
			//return found_path;
		}

		std::vector<map::map_node*> retracePath(const map::map_node& source, map::map_node& target)
		{
			std::vector<map::map_node*> path;
			map::map_node* currentNode = &target;

			while (currentNode != &source)
			{
				path.push_back(currentNode);
				currentNode = currentNode->node_info().parent;
			}

			std::reverse(path.begin(), path.end());

			return path;
		}

		float getDistance(const map::map_node& source, const map::map_node& target)
		{
			const float heuristic = abs(source.location().x() - target.location().x()) +
				abs(source.location().y() - target.location().y());

			return heuristic;
		}

		float getDistance2(map::map_node* source, map::map_node* target)
		{
			const float heuristic = abs(source->location().x() - target->location().x()) +
				abs(source->location().y() - target->location().y());

			return heuristic;
		}

		bool isValid(map::map_graph const& map, float x, float y, const std::vector<char>& walkableLayers)
		{
			for (const auto& node : map)
			{
				if (std::find(walkableLayers.begin(), walkableLayers.end(), node.node_info().kind) == walkableLayers.end())
				{
					if (node.location().x() == x && node.location().y() == y)
					{
						return false;
					}
				}
			}

			return true;
		}

		bool isDestination(const map::map_node& source, const int x, const int y)
		{
			if (source.location().x() == x && source.location().y() == y)
			{
				return true;
			}

			return false;
		}

		void printRoute(std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> route)
		{
			// Render path colors
			for (auto* node : route.second)
			{
				node->tag(graph::node_tag::visited);
			}

			for (auto* node : route.first)
			{
				node->tag(graph::node_tag::path);
			}
		}
		
		void clearRoute(std::pair<std::vector<map::map_node*>, std::vector<map::map_node*>> route)
		{
			// Render path colors
			for (auto* node : route.second)
			{
				node->tag(graph::node_tag::normal);
			}

			for (auto* node : route.first)
			{
				node->tag(graph::node_tag::normal);
			}
		}
	} // namespace ufo
} // namespace kmint
