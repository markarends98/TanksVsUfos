#include "kmint/ufo/state/saucer_global_state.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/tank.hpp"
#include "kmint/ufo/state/saucer/saucer_state_attacking.hpp"

namespace kmint
{
	namespace ufo
	{
		void SaucerGlobalState::onUpdate(const delta_time dt)
		{
			if (context.getCurrentState() != "saucerStateAttacking") {
				for (auto i = saucer_.begin_perceived(); i != saucer_.end_perceived(); ++i)
				{
					auto& a = *i;

					if (typeid(a).name() == typeid(tank).name()) {

						std::cout << "Spotted a tank!\n";
						this->context.changeState(std::make_unique<SaucerStateAttacking>(this->context, saucer_, a));
						return;
					}
				}
			}
			onUpdateHook(dt);
		}
	}
}

