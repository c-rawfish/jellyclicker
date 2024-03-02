#include "nt.h"

namespace nt {
	NTSYSAPI NTSTATUS	NTAPI NtDelayExecution(
		_In_ BOOLEAN Alertable,
		_In_opt_ PLARGE_INTEGER DelayInterval);

	inline decltype(&NtDelayExecution) pNtDelayExecution{};

	void sleep(uint64_t delay_interval) {
		auto grab_nt_delay_execution = [&]() -> bool
			{
				pNtDelayExecution = reinterpret_cast<decltype(pNtDelayExecution)>(
					GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDelayExecution"));

				return true;
			};

		auto _ = grab_nt_delay_execution();

		timeBeginPeriod(1);

		LARGE_INTEGER _delay_interval{};
		_delay_interval.QuadPart = -static_cast<LONGLONG>(delay_interval * static_cast<uint64_t>(10'000));

		pNtDelayExecution(false, &_delay_interval);

		timeEndPeriod(1);
	}
}