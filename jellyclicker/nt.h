#pragma once

#include <Windows.h>
#include <cstdint>

#pragma comment(lib, "winmm.lib")

namespace nt {
	NTSYSAPI NTSTATUS	NTAPI NtDelayExecution(
		_In_ BOOLEAN Alertable,
		_In_opt_ PLARGE_INTEGER DelayInterval);

	void sleep(uint64_t delay_interval);
}