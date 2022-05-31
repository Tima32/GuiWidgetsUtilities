// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <iostream>
#include <windows.h>
#include "../Kernel/Plugins.hpp"
#include "../HelperTools/Screens.hpp"
#include "../HelperTools/Console.hpp"

using namespace std;

class Plugin : public GWU::Plugins::Plugin
{
private:
	std::vector<sf::String> dependencies;
	GWU::Plugins::Plugin::PluginInfo pi
	{
		L"SAOHPBar",
		L"SAOHPBar",
		L"1.0.0 lapha",
		L"Tim",
		L"github.com",
		L"4timonomit4@gmail.com"
	};

public:
	Plugin()
	{
		cout << GWU::console_success;
		cout << "<SAOHPBar:Plugin:Plugin>Info: SAOHPBar Created." << endl;
		cout << GWU::console_default;
	}
	~Plugin()
	{
		cout << "<SAOHPBar:Plugin:Plugin>Info: SAOHPBar destroyed." << endl;
	}

	const PluginInfo& getPluginInfo() const final
	{
		return pi;
	}
	PluginInfo& getPluginInfo() final
	{
		return pi;
	}
	const std::vector<sf::String>& getDependencies() const final
	{
		return dependencies;
	}

	bool enableModule() final
	{
		cout << GWU::console_success;
		cout << "<SAOHPBar:Plugin:enable>Info: enable." << endl;
		cout << GWU::console_default;
		return true;
	};
	bool disableModule() final
	{
		cout << GWU::console_success;
		cout << "<SAOHPBar:Plugin:disable>Info: disable." << endl;
		cout << GWU::console_default;
		return true;
	};
};

Plugin* plugin{ nullptr };

extern "C" __declspec(dllexport) GWU::Plugins::Plugin * GetMainClass()
{
	cout << "<SAOHPBar:GetMainClass>Info: Called." << endl;
	return plugin;
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (plugin == nullptr)
			plugin = new Plugin();
		else
			wcout << "<SAOHPBar:DllMain>Error: The main class has been created." << endl;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		delete plugin;
		break;
	}
	return TRUE;
}

