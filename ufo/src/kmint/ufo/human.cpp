#include "kmint/ufo/human.hpp"

#include <iostream>

#include "kmint/random.hpp"
#include "kmint/ufo/building.hpp"
#include "kmint/ufo/door.hpp"
#include "kmint/ufo/flock_entity.hpp"

namespace kmint::ufo {

	namespace {
		constexpr char const* image_path = "resources/human.png";

		graphics::image human_image() { return graphics::image{ image_path }; }

		math::vector2d random_location() {
			return { random_scalar(60, 900), random_scalar(60, 700) };
		}

	} // namespace

	human::human(const math::vector2d& location) : FlockEntity{ location }, drawable_{ *this, human_image() }
	{
		f_attraction_rt_ = random_scalar(-1.0f, 1.0f);
		f_attraction_gt_ = random_scalar(-1.0f, 1.0f);
		f_attraction_ufo_ = random_scalar(-1.0f, 1.0f);
		f_attraction_door_ = random_scalar(-1.0f, 1.0f);
		f_cohesion_ = random_scalar(0.0f, 1.0f);
		f_separation_ = random_scalar(0.0f, 1.0f);
		f_alignment_ = random_scalar(0.0f, 1.0f);
		
		perception_range_ = 70.0f;
		mass_ = 40.0f;
		max_force_ = 5.0;
		max_speed_ = 10.0f;
		math::vector2d v(random_scalar(-100.0f, 100.0f), random_scalar(-100.0f, 100.0f));
		v = setLength(v, random_scalar(2.0f, 4.0f));
		velocity(v);
	}

	void human::act(const delta_time dt) {
		FlockEntity::act(dt);
	}

	void human::calculate()
	{
		FlockEntity::calculate();
		
		math::vector2d avoidance;
		math::vector2d pursue;
		float perceived_buildings = 0;
		float perceived_doors = 0;
		
		for (auto i = begin_perceived(); i != end_perceived(); ++i)
		{
			auto& a = *i;
			if (typeid(a).name() == typeid(building).name()) {
				const float dist_to = distance(location(), a.location());
				if (dist_to < 15)
				{
					perceived_buildings++;
					avoidance += a.location();
				}
			}

			if (typeid(a).name() == typeid(door).name()) {
				const float dist_to = distance(location(), a.location());
				if (dist_to < 60)
				{
					perceived_doors++;
					pursue = seek(a.location());
				}
			}
		}

		// Door collision
		for (auto i = this->begin_collision(); i != this->end_collision(); ++i) {
			auto& a = *i;

			if (typeid(a).name() == typeid(door).name()) {
				door& tempDoor = dynamic_cast<door&>(*i);
				human* tempHuman = this;

				tempDoor.savedHumans.push_back(tempHuman);

				this->remove();
			}
		}

		if (perceived_buildings > 0)
		{
			avoidance = avoidance / perceived_buildings;
			steering_force_ += evade(avoidance) * 15.0f;
		}

		if (perceived_doors > 0)
		{
			steering_force_ += pursue * f_attraction_door_;
		}
	}
} // namespace kmint::ufo
