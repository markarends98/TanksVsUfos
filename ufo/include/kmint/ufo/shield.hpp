#ifndef KMINT_UFO_SHIELD_HPP
#define KMINT_UFO_SHIELD_HPP

#include <vector>

#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint::ufo {

	namespace {

		graphics::image shield_image() {
			constexpr scalar scale = 1.0;
			return graphics::image{ "resources/shield.png" };
		}

	}
	
	class shield : public play::static_actor
	{
	public:
		shield(math::vector2d location) : play::static_actor{ location }, drawable_{ *this, graphics::image{ shield_image() } } {}
		bool perceivable() const override { return true; }
		ui::drawable const& drawable() const override { return drawable_; }
	private:
		play::image_drawable drawable_;
	};
} // namespace kmint

#endif /* KMINT_UFO_SHIELD_HPP */