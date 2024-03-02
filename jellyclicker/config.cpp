#include "nt.h"
#include "random.h"
#include "gui.h"

namespace input {
	void sleep(const config cfg) {
		if(!cfg.blatant_mode)
			nt::sleep(random::get_delay(cfg.cps, cfg.micro_randomization));
		else
			nt::sleep(random::get_delay(cfg.cps, 0));
	}

	void click(const config cfg, HWND window) {
		POINT mousePos{};
		GetCursorPos(&mousePos);

		PostMessageA(window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(mousePos.x, mousePos.y));
		sleep(cfg);

		if(!cfg.hold) {
			GetCursorPos(&mousePos);
			PostMessageA(window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(mousePos.x, mousePos.y));
			sleep(cfg);
		}
		else {
			sleep(cfg);
		}
	}

	void click_loop(config& cfg) {
		bool click_held = false;

		while(true) {
			if(GetForegroundWindow() != gui::window && cfg.enabled && GetAsyncKeyState(VK_LBUTTON)) {
				if(!click_held && !cfg.blatant_mode) {
					click_held = true;
					cfg.cps = random::get_random_int(cfg.min_cps, cfg.max_cps);
				}

				input::click(cfg, GetForegroundWindow());
				if(!cfg.blatant_mode)
					random::randomization(cfg);
			} else {
				click_held = false;
				nt::sleep(15);
			}
		}
	}
}