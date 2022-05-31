#pragma once
#include <stdint.h>
#include <SFML/System.hpp>
#include <vector>
#include <functional>

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
				Default,
				Text,
				Percent,

				Count
			};
			Tupe t;
		};
		class Text : public Value
		{
		public:
			sf::String v;
		};
		class Percent : public Value
		{
		public:
			float v;
		};

		typedef std::function<bool(Value* v)> CallbackF;
		typedef void const* FunkValueId;

		DataPlugin();
		~DataPlugin();

		FunkValueId registerValue(sf::String name, Value::Tupe tupe, CallbackF f);
		bool unregisterValue(FunkValueId id);

	private:
		struct Element
		{
			sf::String name;          //value name
			Value::Tupe t{ Value::Tupe::Default }; //return tupe
			CallbackF f;              //function reference
		};
		std::vector<Element*> elements;

		bool cpuUsage(Value* v);
	};
}