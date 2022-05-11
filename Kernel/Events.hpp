#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <Windows.h>
#include "ImportExport.hpp"

namespace GWU
{
	class GWU_EXPORT Events
	{
	public:
		class Event
		{
		public:
			size_t type{ 0 };
		};

		bool registerEventType(const sf::String name, size_t module_id);
	private:
	};
}