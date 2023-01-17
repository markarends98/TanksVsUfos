#include "kmint/ufo/state/saucer/saucer_state_wander.hpp"
#include "kmint/ufo/state/saucer/saucer_state_chasing.hpp"
#include "kmint/ufo/human.hpp"

namespace kmint::ufo {
	void SaucerStateWander::onUpdateHook(const delta_time dt)
	{
		for (auto i = saucer_.begin_perceived(); i != saucer_.end_perceived(); ++i)
		{
			auto& a = *i;

			if (typeid(a).name() == typeid(human).name()) {
				this->context.changeState(std::make_unique<SaucerStateChasing>(this->context, saucer_, a));
				return;
			}
		}

		const math::vector2d wander = saucer_.wander();
		saucer_.steeringForce(wander);
		saucer_.update(dt);
	}
}
