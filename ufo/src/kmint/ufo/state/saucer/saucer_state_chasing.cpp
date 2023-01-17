#include "kmint/ufo/state/saucer/saucer_state_chasing.hpp"
#include "kmint/ufo/state/saucer/saucer_state_wander.hpp"
#include "kmint/ufo/human.hpp"

namespace kmint::ufo {
	void SaucerStateChasing::onUpdateHook(const delta_time dt)
	{
		bool can_see_target = false;
		for (auto i = saucer_.begin_perceived(); i != saucer_.end_perceived(); ++i)
		{
			auto& a = *i;
			if (typeid(a).name() == typeid(human).name()) {
				auto* coll = dynamic_cast<human*>(&a);
				if (coll == &target_)
				{
					can_see_target = true;
					break;
				}
			}
		}

		if (!can_see_target)
		{
			context.changeState(std::make_unique<SaucerStateWander>(context, saucer_));
			return;
		}

		const int amount = saucer_.num_colliding_actors();
		if (amount > 0 && collides(saucer_, target_))
		{
			target_.remove();
			context.changeState(std::make_unique<SaucerStateWander>(context, saucer_));
			return;
		}
		
		const math::vector2d pursue = saucer_.pursuit(target_.location(), target_.heading(), target_.velocity());
		saucer_.steeringForce(pursue * 10.0f);
		saucer_.update(dt);
	}
}
