#pragma once
#include <stdint.h>
#include <vector>

#include "ImportExport.hpp"

namespace GWU
{
	struct Screen
	{
		uint32_t size_x{};
		uint32_t size_y{};

		int32_t pos_x{};
		int32_t pos_y{};
	};
	std::vector<Screen> GetScreens();
}