#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/human.hpp"
#include <string>

#include "kmint/random.hpp"
#include "kmint/ufo/state/saucer/saucer_state_wander.hpp"

namespace kmint::ufo {

	namespace {

		char const* color_for(saucer_type type) {
			switch (type) {
			case saucer_type::blue:
				return "Blue";
			case saucer_type::green:
				return "Green";
			case saucer_type::beige:
				return "Beige";
			case saucer_type::yellow:
			default:
				return "Yellow";
			}
		}

		graphics::image image_for(saucer_type type) {
			std::string prefix{ "resources/ship" };
			std::string fn = prefix + color_for(type) + "_manned.png";
			return graphics::image{ fn, 0.3 };
		}
		
		float range_for(saucer_type type) {
			switch (type) {
			case saucer_type::blue:
				return 80.0f;
			case saucer_type::green:
				return 90.0f;
			case saucer_type::beige:
				return 100.0f;
			case saucer_type::yellow:
			default:
				return 110.0f;
			}
		}
	} // namespace

	saucer::saucer(const saucer_type type)
		: ForceDrivenEntity{ {random_scalar(33, 994.f), random_scalar(33, 738.f)} },
		type_{ type },
		drawable_{ *this, image_for(type) },
		perception_range_{ range_for(type) }
	{
		mass_ = 50.0f;
		max_force_ = 10.0f;
		max_speed_ = 30.0f;
		wander_radius_ = 25.0f;
		wander_distance_ = 35.0f;
		wander_jitter_ = 10.0f;
		perception_range_ = 60.0f;
		state_context_.changeState(std::make_unique<SaucerStateWander>(state_context_, *this));
	}

	void saucer::act(const delta_time dt) {
		if(stunned_ > 0)
		{
			changeableDrawable().set_tint(graphics::colors::white);
			time_passed_ += dt;
			if (to_seconds(time_passed_) >= 1) {
				time_passed_ = from_seconds(0);
				stunned_--;
				if(stunned_ == 0)
				{
					changeableDrawable().remove_tint();
				}
			}
		}
		
		if (stunned_ == 0) {
			state_context_.onUpdate(dt);
		}
	}
} // namespace kmint::ufo
