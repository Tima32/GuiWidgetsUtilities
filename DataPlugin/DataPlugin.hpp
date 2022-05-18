#pragma once
#include <stdint.h>
#include <SFML/System.hpp>

namespace DP
{
	class DataPlugin
	{
	public:
		class Value
		{
		public:
			enum class Tupe : uint8_t
			{
				Text,
				Percent,

				Count
			};
			Tupe t;
		};
		class Text : public Value
		{
			sf::String v;
		};
		class Percent : public Value
		{
			float v;
		};


		DataPlugin();
		~DataPlugin();

		void registerValue();
		void unregisterValue();

	private:

	};
}