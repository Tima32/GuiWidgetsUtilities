#include <iostream>
#include <filesystem>
#include <algorithm>
#include <functional>

#include "Plugins.hpp"
#include "Config.hpp"
#include <Windows.h>

using namespace std;
using namespace sf;
namespace fs = std::filesystem;
using namespace GWU;

Plugins Plugins::plugins;

//Plugins::Plugin
bool GWU::Plugins::Plugin::enable()
{
	if (enabled)
		return enabled;

	const auto& dep = getDependencies();
	
	for (size_t di = 0; di < dep.size(); di++)
	{
		const auto& dn = dep[di]; //dependencies name

		//Search in the list of modules.
		auto iter = std::find_if(plugins.pl.begin(), plugins.pl.end(), [&dn](Plugin* p)->bool { return dn == p->getPluginInfo().full_name; });
		if (iter == plugins.pl.end())
		{
			wcout << "<GWU:Plugins:Plugin:enable>Error: Could not find dependency: " << dn.toWideString() << endl;
			return false;
		}

		auto d = *iter; //dependencies

		//Activation check / activation
		if ((*iter)->isEnable() == false)
		{
			//activation
			if (!d->enable())
			{
				wcout << "<GWU::Plugins:Plugin:enable>Error: Failed to activate dependency: " << d->getPluginInfo().full_name.toWideString() << endl;
				return false;
			}
		}
	}

	enabled = enableModule();
	return enabled;
}
bool GWU::Plugins::Plugin::disable()
{
	if (!enabled)
		return true;

	//Search for active dependent plugins.
	for (size_t pi = 0; pi < plugins.pl.size(); pi++)
	{
		if (!plugins.pl[pi]->isEnable())
			continue;

		const auto& dep = plugins.pl[pi]->getDependencies();
		for (const auto& d : dep)
			if (d == getPluginInfo().full_name)
			{
				wcout << "<GWU:Plugins:Plugin:disable>Error: Failed to disable the plugin. one or more dependent plugins are active. (" << 
					plugins.pl[pi]->getPluginInfo().full_name.toWideString() << ')' << endl;
				return false;
			}
	}

	if (!disableModule())
		return false;
	enabled = false;
	return true;
}
bool GWU::Plugins::Plugin::isEnable()
{
	return enabled;
}

Plugins::~Plugins()
{
	unloadPlugins();
}

size_t Plugins::getSize() const
{
	return pl.size();
}

//private
Plugins::Plugins()
{
	wout << TEXT("Plugins init") << endl;
	//MessageBox(nullptr, TEXT("Plugins init"), TEXT("Message"), MB_OK);
}

void GWU::Plugins::loadPlugins()
{
	wstring path = fs::current_path().c_str();
	path += L"\\Plugins";
	for (auto& p : fs::directory_iterator(path))
	{
		if (!p.is_directory())
			continue;
		wcout << L"<Plugins:loadPlugins>Info: Check folder: " << p << endl;
		wstring path = p.path();
		path += L"\\module64.dll";
		wcout << L"<Plugins:loadPlugins>Info: Module path: " << path << endl;

		HMODULE module_handle = LoadLibraryW(path.c_str());
		if (module_handle == NULL)
			continue;

		auto f = GetProcAddress(module_handle, "GetMainClass");
		if (f == nullptr)
		{
			FreeLibrary(module_handle);
			continue;
		}

		typedef GWU::Plugins::Plugin* (*GMC)();
		auto module_main_class = GMC(f)();
		if (module_main_class == nullptr)
		{
			FreeLibrary(module_handle);
			continue;
		}

		module_main_class->getPluginInfo().module_name = path;
		module_main_class->getPluginInfo().id = pl.size();
		module_main_class->getPluginInfo().hm = module_handle;
		pl.push_back(module_main_class);
	}

	for (size_t pi = 0; pi < pl.size(); pi++)
	{
		if (!pl[pi]->enable())
			wcout << "<GWU:Plugins:loadPlugins>Error: Failed to load plugin: " << pl[pi]->getPluginInfo().full_name.toWideString() << endl;
	}

	return;
}
void Plugins::unloadPlugins()
{
	bool all_disabled{};
	do
	{
		all_disabled = true;
		for (size_t i = 0; i < pl.size(); i++)
		{
			all_disabled = pl[i]->disable() && all_disabled ? true : false;
		}
	} while (!all_disabled);

	for (size_t i = 0; i < pl.size(); i++)
		FreeLibrary(pl[i]->getPluginInfo().hm);

	pl.clear();
}