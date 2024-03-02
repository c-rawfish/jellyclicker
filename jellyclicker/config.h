#pragma once
#include <thread>
#include <Windows.h>

struct config;

namespace input {
	void sleep(const config cfg);

	void click(const config cfg, HWND window);

	void click_loop(config& cfg);
}

struct config {
	bool enabled{ false };
	bool hold{ false };
	bool blatant_mode{ false };

	int cps{ 12 };
	int min_cps{ 9 };
	int max_cps{ 14 };

	int randomize_chance{ 2 };
	int deviation{ 2 };
	int micro_randomization{ 100 };
	int spike_chance{ 50 };
	int drop_chance{ 50 };

	config() {
		std::thread click_thread(input::click_loop, std::ref(*this));
		click_thread.detach();
	}
};