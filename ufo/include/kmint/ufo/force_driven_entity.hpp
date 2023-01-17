#ifndef KMINT_UFO_FORCE_DRIVEN_ENTITY_HPP
#define KMINT_UFO_FORCE_DRIVEN_ENTITY_HPP

#include "kmint/play.hpp"

namespace kmint {
	namespace ufo {

		class ForceDrivenEntity : public play::free_roaming_actor {
		public:
			explicit ForceDrivenEntity(const math::vector2d location) : play::free_roaming_actor{ location } {}

			math::vector2d heading() const override { return heading_; }
			void heading(const math::vector2d& heading) { heading_ = heading; }

			void velocity(const math::vector2d& velocity) { velocity_ = velocity; }
			math::vector2d velocity() const { return velocity_; }

			void side(const math::vector2d& side) { side_ = side; }
			math::vector2d side() const { return side_; }
			
			math::vector2d steeringForce() const { return steering_force_; }
			void steeringForce(const math::vector2d& steeringForce) { steering_force_ = steeringForce; }
			void steer(const math::vector2d& steeringForce) { steering_force_ += steeringForce; }

			void act(delta_time dt) override;
			void update(delta_time dt);
			math::vector2d seek(math::vector2d targetPos) const;
			math::vector2d flee(math::vector2d targetPos) const;
			math::vector2d evade(math::vector2d targetPos) const;
			math::vector2d wander();
			math::vector2d pursuit(math::vector2d evaderPos, math::vector2d evaderHeading, math::vector2d evaderVelocity) const;
			float turnaroundTime(math::vector2d agentPos, math::vector2d agentHeading, math::vector2d evaderPos) const;

			bool perceptive() const override { return true; }
		protected:
			math::vector2d steering_force_ = { 1.0, 1.0 };
			math::vector2d velocity_ = { 0.0, 0.0 };
			math::vector2d heading_ = { 1.0, 1.0 };
			math::vector2d side_ = perp(heading_);
			float mass_ = 1;
			float max_force_ = 1.0f;
			float max_speed_ = 1.0f;

			math::vector2d wander_target_ = { 0, 0 };
			float wander_radius_ = 1.0f;
			float wander_distance_ = 1.0f;
			float wander_jitter_ = 1.0f;
		};

	} // namespace ufo
} // namespace kmint

#endif /* KMINT_UFO_FORCE_DRIVEN_ENTITY_HPP */