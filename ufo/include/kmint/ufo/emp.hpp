#ifndef KMINT_UFO_EMP_HPP
#define KMINT_UFO_EMP_HPP

#include <vector>

#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint::ufo {

	namespace {

		graphics::image emp_image() {
			constexpr scalar scale = 1.0;
			return graphics::image{ "resources/emp.png" };
		}

	}
	
	class emp : public play::static_actor
	{
	public:
		emp(math::vector2d location) : play::static_actor{ location }, drawable_{ *this, graphics::image{ emp_image() } } {}
		bool perceivable() const override { return true; }
		ui::drawable const& drawable() const override { return drawable_; }
	private:
		play::image_drawable drawable_;
	};
} // namespace kmint

#endif /* KMINT_UFO_EMP_HPP */