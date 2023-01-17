#ifndef KMINT_UFO_DOOR_HPP
#define KMINT_UFO_DOOR_HPP

#include <vector>

#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint::ufo {
	class door : public play::static_actor
	{
	public:
		door(math::vector2d location) : play::static_actor{ location }, drawable_{ *this, graphics::image{ "" } } {}
		bool must_draw() const override { return false; }
		bool perceivable() const override { return true; }
		ui::drawable const& drawable() const override { return drawable_; }

		std::vector<human*> savedHumans;
	private:
		play::image_drawable drawable_;
	};
} // namespace kmint

#endif /* KMINT_UFO_DOOR_HPP */