#ifndef KMINT_UFO_BUILDING_HPP
#define KMINT_UFO_BUILDING_HPP

#include <vector>

#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint::ufo {
	class building : public play::static_actor
	{
	public:
		building(math::vector2d location) : play::static_actor{ location }, drawable_{ *this, graphics::image{ "" } } {}
		bool must_draw() const override { return false; }
		bool perceivable() const override { return true; }
		ui::drawable const& drawable() const override { return drawable_; }
	private:
		play::image_drawable drawable_;
	};
} // namespace kmint

#endif /* KMINT_UFO_DOCK_HPP */