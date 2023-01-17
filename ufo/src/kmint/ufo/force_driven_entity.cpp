#include "kmint/ufo/force_driven_entity.hpp"
#include "kmint/ufo/transform/transformations.hpp"
#include "kmint/ufo/obstacle.hpp"

#include "kmint/random.hpp"
#include "kmint/ufo/building.hpp"

namespace kmint {
	namespace ufo {
		void ForceDrivenEntity::act(const delta_time dt)
		{
			update(dt);
		}
		
		void ForceDrivenEntity::update(const delta_time dt)
		{
			math::vector2d avoidance;
			float perceived_obstacles = 0;

			for (auto i = begin_perceived(); i != end_perceived(); ++i)
			{
				auto& a = *i;
				if (typeid(a).name() == typeid(obstacle).name()) {
					const float dist_to = distance(location(), a.location());
					if (dist_to < 60)
					{
						perceived_obstacles++;
						avoidance += a.location();
					}
				}
			}

			if (perceived_obstacles > 0)
			{
				avoidance = avoidance / perceived_obstacles;
				steering_force_ += flee(avoidance) * 10.0f;
			}
			
			const math::vector2d acceleration = steering_force_ / mass_;

			const math::vector2d new_velocity = velocity() + (acceleration * to_seconds(dt));
			const math::vector2d truncated_velocity = truncate(new_velocity, max_speed_);

			if (norm2(truncated_velocity) > 0.00000001f)
			{
				heading(normalize(truncated_velocity));
				side(perp(heading()));
			}
			location(location() + (truncated_velocity * to_seconds(dt)));
			velocity(truncated_velocity);
		}

		math::vector2d ForceDrivenEntity::seek(const math::vector2d targetPos) const
		{
			const math::vector2d desired_velocity = normalize(targetPos - location()) * max_speed_;
			return (desired_velocity - velocity());
		}

		math::vector2d ForceDrivenEntity::flee(const math::vector2d targetPos) const
		{
			const math::vector2d desired_velocity = normalize(location() - targetPos) * max_speed_;
			return (desired_velocity - velocity());
		}

		math::vector2d ForceDrivenEntity::evade(const math::vector2d targetPos) const
		{
			const math::vector2d to_target_pos = targetPos - location();
			const float look_ahead_time = length(to_target_pos) / max_speed_;
			return flee(targetPos * look_ahead_time);
		}
		
		math::vector2d ForceDrivenEntity::wander()
		{
			const float random_x = random_scalar(-1.0f, 1.0f);
			const float random_y = random_scalar(-1.0f, 1.0f);
			
			wander_target_ += math::vector2d{ random_x * wander_jitter_, random_y * wander_jitter_ };
			wander_target_ = normalize(wander_target_);
			wander_target_ *= wander_radius_;

			const math::vector2d target_local = wander_target_ + math::vector2d{ wander_distance_, 0 };
			return target_local;
		}

		math::vector2d ForceDrivenEntity::pursuit(const math::vector2d evaderPos, const math::vector2d evaderHeading, const math::vector2d evaderVelocity) const
		{
			const math::vector2d to_evader = evaderPos - location();
			const float relative_heading = dot(heading(), evaderHeading);
			if ((dot(to_evader, heading()) > 0.0f) && (relative_heading < -0.95f))
			{
				return seek(evaderPos);
			}

			float look_ahead_time = static_cast<float>(length(to_evader)) / (max_speed_ + static_cast<float>(length(evaderVelocity)));
			look_ahead_time += turnaroundTime(location(), heading(), evaderPos);
			return seek(evaderPos + evaderVelocity * look_ahead_time);
		}

		float ForceDrivenEntity::turnaroundTime(const math::vector2d agentPos, const math::vector2d agentHeading, const math::vector2d evaderPos) const
		{
			const math::vector2d to_target = normalize(evaderPos - agentPos);
			const float dot_p = dot(agentHeading, to_target);
			const float coefficient = 0.5;
			return static_cast<float>((dot_p - 1.0f)) * -coefficient;
		}
	} // namespace ufo
} // namespace kmint
