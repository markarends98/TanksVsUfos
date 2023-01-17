#include "kmint/ufo/state/saucer/saucer_state_attacking.hpp"
#include "kmint/ufo/state/saucer/saucer_state_wander.hpp"

namespace kmint::ufo {
	void SaucerStateAttacking::onUpdateHook(const delta_time dt)
	{
		bool can_see_target = false;
		for (auto i = saucer_.begin_perceived(); i != saucer_.end_perceived(); ++i)
		{
			auto& a = *i;
			if (typeid(a).name() == typeid(tank).name()) {
				auto* coll = dynamic_cast<tank*>(&a);
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
			target_.handleSaucerAttack(saucer_);
			context.changeState(std::make_unique<SaucerStateWander>(context, saucer_));
			return;
		}

		const math::vector2d seek = saucer_.seek(target_.location());
		saucer_.steeringForce(seek * 10.0f);
		saucer_.update(dt);
	}
}
