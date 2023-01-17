#include "kmint/ufo/state/tank/tank_state_roaming.hpp"
#include "kmint/random.hpp"
#include "kmint/ufo/emp.hpp"
#include "kmint/ufo/human.hpp"
#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/shield.hpp"
#include "kmint/ufo/state/tank/tank_state_finding.hpp"
#include "kmint/ufo/state/tank/tank_state_fleeing.hpp"

namespace kmint::ufo {
	bool TankStateRoaming::onUpdateHook(const delta_time dt)
	{
		// Targeting & fleeing behaviour
		for (auto i = tank_.begin_perceived(); i != tank_.end_perceived(); ++i)
		{
			auto& act = *i;

			if (typeid(act).name() == typeid(ufo::saucer).name()) {
				float damage = 50;
				if (tank_.hasShield)
				{
					damage = 20;
				}

				const float dist = static_cast<float>(1 - tank_.currentDamage / 100) * static_cast<float>(1 - damage / 100);

				if(dist >= 0.5f)
				{
					std::unique_ptr<TankStateFinding> state = std::make_unique<TankStateFinding>(context, tank_, getClosestObject<emp>());
					context.changeState(std::move(state));
				}
				else if(dist >= 0.3f)
				{
					std::unique_ptr<TankStateFinding> state = std::make_unique<TankStateFinding>(context, tank_, getClosestObject<shield>());
					context.changeState(std::move(state));
				}
				else
				{
					std::unique_ptr<TankStateFleeing> state = std::make_unique<TankStateFleeing>(context, tank_, act);
					context.changeState(std::move(state));
				}
				
				return false;
			}
		}
		
		for (auto i = this->tank_.begin_collision(); i != this->tank_.end_collision(); ++i) {
			try
			{
				human* a = &dynamic_cast<human&>(*i);
				
				switch (this->tank_.getTankType())
				{
				case tank_type::red:
					this->tank_.killedHumans.push_back(a);
					break;
				case tank_type::green:
					a->geneticScore++;
					this->tank_.savedHumans.push_back(a);
					break;
				}
				
				a->remove();
			}
			catch (const std::bad_cast& e) {}
		}
		return true;
	}
}
