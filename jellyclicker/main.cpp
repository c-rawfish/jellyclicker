#include <Windows.h>
#include "gui.h"
#include "config.h"
#include "nt.h"

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow) {
	config cfg{};

	gui::CreateHWindow("jellyclicker");
	gui::CreateDevice();
	gui::CreateImGui();

	while(gui::isRunning) {
		gui::BeginRender();
		gui::Render(cfg);
		gui::EndRender();

		nt::sleep(15);
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return 0;
}