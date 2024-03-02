#include "random.h"

namespace random {
	int get_random_int(int min, int max) {
		std::uniform_int_distribution dist{ min, max };

		return dist(mersenne);
	}

	void randomization(config& cfg) {
		int ticket{ get_random_int(1, 100) };
		if(ticket <= cfg.randomize_chance / 2 || ticket >= cfg.randomize_chance / 2) {
			int lower{ std::min<int>(cfg.drop_chance, cfg.spike_chance) };
			int deviation{};

			if(lower == cfg.drop_chance) {
				if(ticket <= cfg.drop_chance) {
					deviation = random::get_random_int(-cfg.deviation, -1);
				} else {
					deviation = random::get_random_int(1, cfg.deviation);
				}
			} else {
				if(ticket <= cfg.spike_chance) {
					deviation = random::get_random_int(1, cfg.deviation);
				} else {
					deviation = random::get_random_int(-cfg.deviation, -1);
				}
			}

			cfg.cps = std::clamp<int>(cfg.cps + deviation, cfg.min_cps, cfg.max_cps);
		}
	}

	int get_delay(const int cps, const int micro_random) {
		return get_random_int(500 - (micro_random / 2), 500 + (micro_random / 2)) / cps;
	}
}