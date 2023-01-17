#ifndef KMINT_UFO_FLOCK_ENTITY_HPP
#define KMINT_UFO_FLOCK_ENTITY_HPP

#include "force_driven_entity.hpp"
#include "kmint/play.hpp"

namespace kmint {
	namespace ufo {
		class FlockEntity : public ForceDrivenEntity {
		public:
			explicit FlockEntity(const math::vector2d location) : ForceDrivenEntity{ location }, drawable_{ *this,  graphics::image {std::string("") } } {}
			const ui::drawable& drawable() const override { return drawable_; }
			bool perceptive() const override { return true; }
			virtual void calculate();

			void act(delta_time dt) override;
			scalar perception_range() const override { return perception_range_; }

			float f_cohesion_ = 1.0f;
			float f_separation_ = 1.0f;
			float f_alignment_ = 1.0f;
			float f_avoidance_ = 10.0f;

			math::vector2d cohesion_{ 0.0f, 0.0f };
			math::vector2d separation_{ 0.0f, 0.0f };
			math::vector2d alignment_{ 0.0f, 0.0f };
		protected:
			float perception_range_ = 1.0f;
			play::image_drawable drawable_;
		};
	} // namespace ufo
} // namespace kmint

#endif /* KMINT_UFO_FORCE_DRIVEN_ENTITY_HPP */