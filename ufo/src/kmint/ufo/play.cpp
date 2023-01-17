#include "kmint/ufo/play.hpp"
#include "kmint/main.hpp" // voor de main loop
#include "kmint/play.hpp"
#include "kmint/ufo/andre.hpp"
#include "kmint/ufo/human.hpp"
#include "kmint/ufo/resources.hpp"
#include "kmint/ufo/saucer.hpp"
#include "kmint/ufo/tank.hpp"
#include "kmint/ufo/node_algorithm.hpp"
#include "kmint/ui.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "kmint/ufo/building.hpp"
#include "kmint/ufo/door.hpp"
#include "kmint/ufo/emp.hpp"
#include "kmint/ufo/shield.hpp"
#include "kmint/ufo/obstacle.hpp"


namespace kmint::ufo {

	std::unique_ptr<human>* createParent(std::vector<std::unique_ptr<human>*> humans)
	{
		std::vector<int> humanWeights;

		for(auto human : humans)
		{
			if(human->get()->geneticScore != 0)
			{
				humanWeights.push_back(human->get()->geneticScore);
			}
			else
			{
				humanWeights.push_back(1);
			}
		}

		std::random_device device;
		std::mt19937 engine(device());
		std::discrete_distribution<> dist(humanWeights.begin(), humanWeights.end());

		return humans[dist(engine)];
	}

	// Generate a random float number between a range
	float randomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}
	
	int play() {
		// een app object is nodig om
		ui::app app{};

		delta_time t_passed_{};
		int roundCounter = 0;
		bool firstRound = true;

		//  maak een venster aan
		ui::window window{ app.create_window({1024, 768}, "kmint", 1.0) };

		// maak een podium aan
		play::stage s{ {1024, 768} };

		auto m = map();
		auto& graph = m.graph();

		s.build_actor<play::background>(math::size(1024, 768),
			graphics::image{ m.background_image() });
		s.build_actor<play::map_actor>(math::vector2d{ 0.f, 0.f }, m.graph());
		
		// Building walls
		std::vector<math::vector2d> walls = {
			{584,72},
			{600,72},
			{616,72},
			{632,72},
			{648,72},
			{664,72},
			{680,72},
			{696,72},
			{712,72},
			{728,72},
			{584,88},
			{600,88},
			{616,88},
			{632,88},
			{648,88},
			{664,88},
			{680,88},
			{696,88},
			{712,88},
			{728,88},
			{584,104},
			{600,104},
			{616,104},
			{632,104},
			{648,104},
			{664,104},
			{680,104},
			{696,104},
			{712,104},
			{728,104},
			{584,120},
			{600,120},
			{616,120},
			{632,120},
			{648,120},
			{664,120},
			{712,120},
			{728,120},
			{584,136},
			{616,136},
			{584,216},
			{600,216},
			{616,216},
			{632,216},
			{648,216},
			{664,216},
			{584,232},
			{600,232},
			{616,232},
			{632,232},
			{648,232},
			{664,232},
			{584,248},
			{600,248},
			{616,248},
			{632,248},
			{648,248},
			{664,248},
			{584,264},
			{600,264},
			{616,264},
			{632,264},
			{648,264},
			{664,264},
			{584,280},
			{600,280},
			{616,280},
			{632,280},
			{648,280},
			{664,280},
			{584,296},
			{600,296},
			{616,296},
			{632,296},
			{648,296},
			{664,296},
			{584,312},
			{600,312},
			{648,312},
			{664,312},
			{584,408},
			{600,408},
			{616,408},
			{632,408},
			{648,408},
			{664,408},
			{680,408},
			{584,424},
			{600,424},
			{616,424},
			{632,424},
			{648,424},
			{664,424},
			{680,424},
			{584,440},
			{600,440},
			{616,440},
			{632,440},
			{648,440},
			{664,440},
			{680,440},
			{584,456},
			{600,456},
			{616,456},
			{632,456},
			{648,456},
			{664,456},
			{680,456},
			{440,472},
			{456,472},
			{472,472},
			{488,472},
			{504,472},
			{584,472},
			{600,472},
			{616,472},
			{632,472},
			{648,472},
			{664,472},
			{680,472},
			{440,488},
			{456,488},
			{472,488},
			{488,488},
			{504,488},
			{584,488},
			{600,488},
			{616,488},
			{632,488},
			{648,488},
			{664,488},
			{680,488},
			{440,504},
			{456,504},
			{472,504},
			{488,504},
			{504,504},
			{328,520},
			{344,520},
			{360,520},
			{376,520},
			{392,520},
			{408,520},
			{424,520},
			{440,520},
			{456,520},
			{472,520},
			{488,520},
			{504,520},
			{328,536},
			{344,536},
			{360,536},
			{376,536},
			{392,536},
			{408,536},
			{424,536},
			{440,536},
			{456,536},
			{472,536},
			{488,536},
			{504,536},
			{328,552},
			{344,552},
			{360,552},
			{376,552},
			{392,552},
			{408,552},
			{424,552},
			{440,552},
			{456,552},
			{472,552},
			{488,552},
			{504,552},
			{328,568},
			{344,568},
			{360,568},
			{376,568},
			{392,568},
			{408,568},
			{424,568},
			{440,568},
			{456,568},
			{472,568},
			{488,568},
			{504,568},
			{328,584},
			{344,584},
			{360,584},
			{376,584},
			{392,584},
			{408,584},
			{424,584},
			{440,584},
			{456,584},
			{472,584},
			{488,584},
			{504,584},
			{328,600},
			{344,600},
			{360,600},
			{376,600},
			{392,600},
			{408,600},
			{424,600},
			{440,600},
			{456,600},
			{472,600},
			{488,600},
			{504,600},
			{328,616},
			{344,616},
			{360,616},
			{376,616},
			{392,616},
			{408,616},
			{424,616},
			{456,616},
			{472,616},
			{488,616},
			{504,616},
			{328,632},
			{344,632},
			{360,632},
			{376,632},
			{424,632}
		};
		
		for (auto i = walls.begin(); i != walls.end(); ++i)
		{
			auto a = *i;
			s.build_actor<ufo::building>(a);
		}

		// Doors
		std::vector<math::vector2d> doors = {
			{680,120},
			{696,120},
			{600,136},
			{680,136},
			{696,136},
			{616,312},
			{632,312},
			{616,328},
			{632,328},
			{456,616},
			{392,632},
			{408,632},
			{456,632},
			{392,648},
			{408,648}
		};

		for (auto i = doors.begin(); i != doors.end(); ++i)
		{
			auto a = *i;
			s.build_actor<ufo::door>(a);
		}
		
		// Top / bottom border
		for (float i = 0; i < 1024; i += 16) {
			math::vector2d locationTop = { i,0 };
			math::vector2d locationBottom = { i,768 };

			s.build_actor<ufo::obstacle>(locationTop);
			s.build_actor<ufo::obstacle>(locationBottom);
		}

		// Left / right border
		for (float i = 0; i < 768; i += 16) {
			math::vector2d locationLeft = { 0,i };
			math::vector2d locationRight = { 1024,i };

			s.build_actor<ufo::obstacle>(locationLeft);
			s.build_actor<ufo::obstacle>(locationRight);
		}

		// Create humans

		for (std::size_t h{ 0 }; h < 100; ++h) {
			math::vector2d random_location = random_node_of_kind(m, 'R').location();
			s.build_actor<ufo::human>(random_location);
		}

		// Create EMP's
		for (int i = 0; i < 3; i++) {
			math::vector2d random_location = random_node_of_kind(m, 'R').location();
			s.build_actor<ufo::emp>(random_location);
		}

		// Create Shields
		for (int i = 0; i < 3; i++) {
			math::vector2d random_location = random_node_of_kind(m, 'R').location();
			s.build_actor<ufo::shield>(random_location);
		}

		s.build_actor<ufo::andre>(graph, ufo::random_node_of_kind(m, 'R'));
		s.build_actor<ufo::tank>(s, graph, ufo::random_node_of_kind(m, 'T'), tank_type::red);
		s.build_actor<ufo::tank>(s, graph, ufo::random_node_of_kind(m, 'T'), tank_type::green);
		s.build_actor<ufo::saucer>(saucer_type::blue);
		s.build_actor<ufo::saucer>(saucer_type::green);
		s.build_actor<ufo::saucer>(saucer_type::beige);
		s.build_actor<ufo::saucer>(saucer_type::yellow);

		// Maak een event_source aan (hieruit kun je alle events halen, zoals
		// toetsaanslagen)
		ui::events::event_source event_source{};

		// main_loop stuurt alle actors aan.
		main_loop(s, window, [&](delta_time dt, loop_controls& ctl) {
			// gebruik dt om te kijken hoeveel tijd versterken is
			// sinds de vorige keer dat deze lambda werd aangeroepen
			// loop controls is een object met eigenschappen die je kunt gebruiken om de
			// main-loop aan te sturen.

			t_passed_ += dt;

			if(to_seconds(t_passed_) >= 1)
			{
				roundCounter++;
				std::cout << "ROUND: " << roundCounter << std::endl;
				// Reset round
				if(roundCounter >= 200)
				{
					// UNCOMMENT THIS IF NODE TAGS ARE NOT RESET
					//graph.untag_all();
					std::vector<std::vector<float>> newHumanValues;
					// Genetic Algorithm
					auto survivingHumans = s.getActors<ufo::human>();

					// Tank survivors
					for (auto tank : s.getActors<ufo::tank>())
					{
						for (auto savedHuman : tank->get()->savedHumans)
						{
							std::unique_ptr<human>* temp = new std::unique_ptr<human>(savedHuman);
							survivingHumans.push_back(temp);
						}
					}

					// Building survivors
					for (auto door : s.getActors<ufo::door>())
					{
						for (auto savedHuman : door->get()->savedHumans)
						{
							std::unique_ptr<human>* temp = new std::unique_ptr<human>(savedHuman);
							survivingHumans.push_back(temp);
						}
					}

					for (auto human : survivingHumans)
					{
						human->get()->geneticScore += 10;
					}

					// Genetic algorithm
					for (int i = 0; i < 100; i++)
					{
						// Create parents
						std::unique_ptr<human>* firstParent = createParent(survivingHumans);
						std::unique_ptr<human>* secondParent = createParent(survivingHumans);

						firstParent->get()->geneticScore /= 2;
						secondParent->get()->geneticScore /= 2;

						// Generate forces based on parents for human in new generation
						float cohesion = (firstParent->get()->f_cohesion_ + secondParent->get()->f_cohesion_) / 2;
						float seperation = (firstParent->get()->f_separation_ + secondParent->get()->f_separation_) / 2;
						float alignment = (firstParent->get()->f_alignment_ + secondParent->get()->f_alignment_) / 2;

						float f_attraction_rt = (firstParent->get()->f_attraction_rt_ + secondParent->get()->f_attraction_rt_) / 2;
						float f_attraction_gt = (firstParent->get()->f_attraction_gt_ + secondParent->get()->f_attraction_gt_) / 2;
						float f_attraction_ufo = (firstParent->get()->f_attraction_ufo_ + secondParent->get()->f_attraction_ufo_) / 2;
						float f_attraction_door = (firstParent->get()->f_attraction_door_ + secondParent->get()->f_attraction_door_) / 2;

						// Generate mutation chance
						int mutationPercentage = 20;
						float mutationRate = 0.10;

						if ((rand() % 100) < mutationPercentage)
						{
							int zeroOrOne = rand() % 2;
							float mutationValue = randomFloat(0.0, mutationRate);

							if (zeroOrOne == 1) {
								cohesion += mutationValue;
								seperation += mutationValue;
								alignment += mutationValue;

								f_attraction_rt += mutationValue;
								f_attraction_gt += mutationValue;
								f_attraction_ufo += mutationValue;
								f_attraction_door += mutationValue;
							}
							else {
								cohesion -= mutationValue;
								seperation -= mutationValue;
								alignment -= mutationValue;

								f_attraction_rt -= mutationValue;
								f_attraction_gt -= mutationValue;
								f_attraction_ufo -= mutationValue;
								f_attraction_door -= mutationValue;
							}
						}

						// Validate forces to stay within allowed range
						if (cohesion < 0 || cohesion > 1) { cohesion = randomFloat(0.0, 1.0); }
						if (seperation < 0 || seperation > 1) { seperation = randomFloat(0.0, 1.0); }
						if (alignment < 0 || alignment > 1) { alignment = randomFloat(0.0, 1.0); }
						if (f_attraction_rt < -1 || f_attraction_rt > 1) { f_attraction_rt = randomFloat(-1.0, 1.0); }
						if (f_attraction_gt < -1 || f_attraction_gt > 1) { f_attraction_gt = randomFloat(-1.0, 1.0); }
						if (f_attraction_ufo < -1 || f_attraction_ufo > 1) { f_attraction_ufo = randomFloat(-1.0, 1.0); }
						if (f_attraction_door < -1 || f_attraction_door > 1) { f_attraction_door = randomFloat(-1.0, 1.0); }

						std::vector<float> flockValues;
						flockValues.push_back(cohesion);
						flockValues.push_back(seperation);
						flockValues.push_back(alignment);
						flockValues.push_back(f_attraction_rt);
						flockValues.push_back(f_attraction_gt);
						flockValues.push_back(f_attraction_ufo);
						flockValues.push_back(f_attraction_door);

						newHumanValues.push_back(flockValues);
					}
					
					// Remove humans
					std::vector<std::unique_ptr<human>*> humans = s.getActors<human>();
					for (std::unique_ptr<human>* human : humans) {
						human->get()->remove();
					}

					// Remove EMP's
					std::vector<std::unique_ptr<ufo::emp>*> emps = s.getActors<ufo::emp>();
					for (std::unique_ptr<ufo::emp>* emp : emps) {
						emp->get()->remove();
					}

					// Remove Shields
					std::vector<std::unique_ptr<ufo::shield>*> shields = s.getActors<ufo::shield>();
					for (std::unique_ptr<ufo::shield>* shield : shields) {
						shield->get()->remove();
					}

					// Remove UFO's
					std::vector<std::unique_ptr<ufo::saucer>*> ufos = s.getActors<ufo::saucer>();
					for (std::unique_ptr<ufo::saucer>* ufo : ufos) {
						ufo->get()->remove();
					}

					// Remove tanks
					std::vector<std::unique_ptr<ufo::tank>*> tanks = s.getActors<ufo::tank>();
					for (std::unique_ptr<ufo::tank>* tank : tanks) {
						tank->get()->remove();
					}
					
					// Remove andre
					std::vector<std::unique_ptr<ufo::andre>*> andres = s.getActors<ufo::andre>();
					for (std::unique_ptr<ufo::andre>* andre : andres) {
						andre->get()->remove();
					}

					// Empty saved humans in buildings (doors)
					std::vector<std::unique_ptr<ufo::door>*> doors = s.getActors<ufo::door>();
					for (std::unique_ptr<ufo::door>* door : doors) {
						door->get()->savedHumans.clear();
					}

					// Create humans
					for (std::size_t h{ 0 }; h < 100; ++h) {
						math::vector2d random_location = random_node_of_kind(m, 'R').location();
						auto& human = s.build_actor<ufo::human>(random_location);

						// Apply genetic values to new generation of humans
						human.f_cohesion_ = newHumanValues[h][0];
						human.f_separation_ = newHumanValues[h][1];
						human.f_alignment_ = newHumanValues[h][2];
						human.f_attraction_rt_ = newHumanValues[h][3];
						human.f_attraction_gt_ = newHumanValues[h][4];
						human.f_attraction_ufo_ = newHumanValues[h][5];
						human.f_attraction_door_ = newHumanValues[h][6];
					}

					// Create EMP's
					for (int i = 0; i < 3; i++) {
						math::vector2d random_location = random_node_of_kind(m, 'R').location();

						s.build_actor<ufo::emp>(random_location);
					}

					// Create shields
					for (int i = 0; i < 3; i++) {
						math::vector2d random_location = random_node_of_kind(m, 'R').location();

						s.build_actor<ufo::shield>(random_location);
					}

					// Create tanks
					s.build_actor<ufo::tank>(s, graph, ufo::random_node_of_kind(m, 'T'), tank_type::red);
					s.build_actor<ufo::tank>(s, graph, ufo::random_node_of_kind(m, 'T'), tank_type::green);

					// Create andre
					s.build_actor<ufo::andre>(graph, ufo::random_node_of_kind(m, 'R'));

					// Create UFO's
					s.build_actor<ufo::saucer>(saucer_type::blue);
					s.build_actor<ufo::saucer>(saucer_type::green);
					s.build_actor<ufo::saucer>(saucer_type::beige);
					s.build_actor<ufo::saucer>(saucer_type::yellow);
					roundCounter = 0;
				}

				t_passed_ = from_seconds(0);
			}

			for (ui::events::event& e : event_source) {
				// event heeft een methode handle_quit die controleert
				// of de gebruiker de applicatie wilt sluiten, en zo ja
				// de meegegeven functie (of lambda) aanroept om met het
				// bijbehorende quit_event
				//
				e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
				e.handle_key_up([&](auto ke) {
					switch (ke.key) {
					case ui::events::key::p:
						ctl.pause = !ctl.pause;
						break;
					case ui::events::key::r:
						ctl.render = !ctl.render;
						break;
					case ui::events::key::opening_bracket:
						ctl.time_scale /= 2.0;
						break;
					case ui::events::key::closing_bracket:
						ctl.time_scale *= 2.0;
						break;
					default:
						break;
					}
					});
			}
			});
		return 0;
	}

} // namespace kmint::ufo
