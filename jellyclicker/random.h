#pragma once

#include <random>
#include "config.h"

namespace random {
	inline std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

	int get_random_int(int min, int max);
	void randomization(config& cfg);

	int get_delay(const int cps, const int micro_random);
}