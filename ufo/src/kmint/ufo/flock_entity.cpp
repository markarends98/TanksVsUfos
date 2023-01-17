#include "kmint/ufo/flock_entity.hpp"

#include "kmint/math/vector2d.hpp"
#include "kmint/ufo/human.hpp"

namespace kmint::ufo {
	void FlockEntity::calculate()
	{
		steering_force_ = {};
		steering_force_ += cohesion_ * f_cohesion_;
		steering_force_ += separation_ * f_separation_;
		steering_force_ += alignment_ * f_alignment_;
	}

	void FlockEntity::act(const delta_time dt)
	{
		math::vector2d steering_force;			// Separation
		math::vector2d average_heading;			// Alignment
		math::vector2d center_of_mass;			// Cohesion

		cohesion_ = {};
		separation_ = {};
		alignment_ = {};
		
		int perceived_neighbors = 0;

		for (auto i = begin_perceived(); i != end_perceived(); ++i) {
			actor& act = *i;

			if (typeid(act).name() == typeid(human).name()) {
				auto& neighbor = dynamic_cast<FlockEntity&>(act);
				if (sees(*this, neighbor)) {
					const math::vector2d to_agent = location() - neighbor.location();	// Separation
					steering_force += normalize(to_agent) / length(to_agent);			// Separation
					average_heading += neighbor.heading();								// Alignment
					center_of_mass += neighbor.location();								// Cohesion

					perceived_neighbors++;
				}
			}
		}
		
		if (perceived_neighbors > 0) {
			const auto count = static_cast<scalar>(perceived_neighbors);
			separation_ = steering_force;					// Separation
			alignment_ = average_heading / count;			// Alignment
			alignment_ = average_heading - heading();		// Alignment

			center_of_mass = center_of_mass / count;		// Cohesion
			cohesion_ = seek(center_of_mass);				// Cohesion
		}
		calculate();
		ForceDrivenEntity::act(dt);
	}
}
