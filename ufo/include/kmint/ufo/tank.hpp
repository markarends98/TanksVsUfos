#ifndef KMINT_UFO_TANK_HPP
#define KMINT_UFO_TANK_HPP

#include "human.hpp"
#include "saucer.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "context/state_context.hpp"

namespace kmint {
namespace ufo {

enum class tank_type { red, green };

class tank : public play::map_bound_actor {
public:
	tank(play::stage& s, map::map_graph& g, map::map_node& initial_node, tank_type t);
	// wordt elke game tick aangeroepen
	void act(delta_time dt) override;
	ui::drawable const& drawable() const override { return drawable_; }
	// als incorporeal false is, doet de actor mee aan collision detection
	bool incorporeal() const override { return false; }
	// geeft de lengte van een zijde van de collision box van deze actor terug.
	// Belangrijk voor collision detection
	scalar collision_range() const override { return 16.0; }
	// geeft aan dat de tank andere actors kan zien
	bool perceptive() const override { return true; }
	// geeft het bereik aan waarbinnen een tank
	// andere actors kan waarnemen.
	scalar perception_range() const override { return 200.f; }
	void repair() { currentDamage = 0; }
	tank_type getTankType() const { return type_; }
	void handleSaucerAttack(saucer& saucer);
	std::vector<human*> savedHumans;
	std::vector<human*> killedHumans;

	play::stage& stage;
	map::map_graph& graph;
	int currentDamage = 0;

	bool hasEMP = false;
	bool hasShield = false;
private:
	play::image_drawable drawable_;
	delta_time t_since_move_{};
	tank_type type_;
	StateContext stateContext;
};

} // namespace ufo
} // namespace kmint

#endif /* KMINT_UFO_TANK_HPP */
