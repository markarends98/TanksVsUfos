#include "kmint/ufo/andre.hpp"
#include "kmint/graphics.hpp"
#include "kmint/ufo/node_algorithm.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/state/andre/andre_state_roaming.hpp"
#include <iostream>

namespace kmint::ufo {

namespace {

graphics::image andre_image() {
  constexpr scalar scale = 1.0;
  return graphics::image{"resources/andre.png"};
}

} // namespace
andre::andre(map::map_graph& g, map::map_node& initial_node)
	: play::map_bound_actor{ initial_node }, drawable_{ *this,
													 graphics::image{
														 andre_image()}  }
{
	std::unique_ptr<AndreStateRoaming> state = std::make_unique<AndreStateRoaming>(this->stateContext, *this, g);
	this->stateContext.changeState(std::move(state));
}

void andre::act(delta_time dt) {
	stateContext.onUpdate(dt);
}

} // namespace kmint::ufo
