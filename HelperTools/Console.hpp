#pragma once
#include <stdint.h>
#include <iostream>

namespace GWU
{
	enum class ConsoleTextColor : uint16_t
	{
		Default = 7,
		Success = 2,
		Warning = 6,
		Error = 4,
	};
	void SetConsoleTextColor(ConsoleTextColor color);

	struct ConsoleT { public: ConsoleTextColor c; ConsoleT(ConsoleTextColor c) { this->c = c; } };
	extern ConsoleT console_default;
	extern ConsoleT console_success;
	extern ConsoleT console_warning;
	extern ConsoleT console_error;
}

std::ostream& operator << (std::ostream& os, const GWU::ConsoleT& c);