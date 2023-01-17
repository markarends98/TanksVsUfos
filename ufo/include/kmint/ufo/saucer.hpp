#ifndef KMINT_UFO_SAUCER_HPP
#define KMINT_UFO_SAUCER_HPP
#include "force_driven_entity.hpp"
#include "context/state_context.hpp"
#include "kmint/play.hpp"

namespace kmint::ufo {
	enum class saucer_type { blue, green, beige, yellow };
	class saucer : public ForceDrivenEntity {
	public:
		saucer(saucer_type type);
		saucer_type type() const noexcept { return type_; }
		ui::drawable const& drawable() const override { return drawable_; }
		play::image_drawable& changeableDrawable() { return drawable_; }
		void act(delta_time dt) override;
		// participates in collisions
		bool incorporeal() const override { return false; }
		scalar collision_range() const override { return 32.0; }
		bool perceptive() const override { return true; }
		scalar perception_range() const override { return perception_range_; }
		void stun(const int stunDuration) { stunned_ = stunDuration; }
	private:
		saucer_type type_;
		play::image_drawable drawable_;
		StateContext state_context_;
		float perception_range_;
		int stunned_ = 0;
		delta_time time_passed_{};
	};

} // namespace kmint::ufo
#endif
