#ifndef KMINT_UFO_HUMAN_HPP
#define KMINT_UFO_HUMAN_HPP

#include "kmint/play.hpp"
#include "flock_entity.hpp"

namespace kmint::ufo {

	class human : public FlockEntity {
	public:
		human(const math::vector2d& location);
		const ui::drawable& drawable() const override { return drawable_; }
		// participates in collisions
		bool incorporeal() const override { return false; }
		void act(delta_time dt) override;
		void calculate() override;
		scalar collision_range() const override { return 10.0f; }

		float f_attraction_rt_ = 1.0f;
		float f_attraction_gt_ = 1.0f;
		float f_attraction_ufo_ = 1.0f;
		float f_attraction_door_ = 1.0f;
		
		int geneticScore = 0;
	private:
		play::image_drawable drawable_;
		
		math::vector2d attraction_rt_;
		math::vector2d attraction_gt_;
		math::vector2d attraction_ufo_;
		math::vector2d attraction_door_;
	};

} // namespace kmint::ufo

#endif /* KMINT_UFO_HUMAN_HPP */
