#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <Windows.h>
#include "ImportExport.hpp"


namespace GWU
{
	class GWU_EXPORT Plugins
	{
	public:
		class GWU_EXPORT Plugin
		{
		public:
			struct PluginInfo
			{
				inline PluginInfo() = default;
				inline PluginInfo(
					sf::String name,
					sf::String full_name,
					sf::String version,
					sf::String author,
					sf::String web_site,
					sf::String email)
					:
					name(name), full_name(full_name), version(version), author(author), web_site(web_site), email(email)
				{};

				sf::String name;
				sf::String full_name;
				sf::String version;
				sf::String author;
				sf::String web_site;
				sf::String email;

			private:
				//Filled with kernel
				sf::String module_name; //full path to the module
				size_t id{size_t(-1)};  //module number in the list
				HMODULE hm{ nullptr };  //module handle

				friend Plugins;
			};

			virtual ~Plugin() = default;

			virtual const PluginInfo& getPluginInfo() const = 0;
			virtual const std::vector<sf::String>& getDependencies() const = 0;

			bool enable();
			bool disable();
			bool isEnable();

		protected:
			virtual bool enableModule() = 0;
			virtual bool disableModule() = 0;

		private:
			virtual PluginInfo& getPluginInfo() = 0;

			bool enabled{ false };

			friend Plugins;
		};
		static Plugins plugins;

		~Plugins();

		size_t getSize() const;

		void loadPlugins();
		void unloadPlugins();
	private:
		Plugins();

		std::vector<Plugin*> pl;

		friend Plugin;
	};
}