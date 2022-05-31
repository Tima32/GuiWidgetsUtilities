// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <iostream>
#include <windows.h>
#include "../Kernel/Plugins.hpp"
#include "../HelperTools/Screens.hpp"
#include "../HelperTools/Console.hpp"
#include "DataPlugin.hpp"

using namespace std;

class Plugin : public GWU::Plugins::Plugin
{
private:
	std::vector<sf::String> dependencies;
	GWU::Plugins::Plugin::PluginInfo pi
	{
		L"DataPlugin",
		L"Base:DataPlugin",
		L"1.0.0 lapha",
		L"Tim",
		L"github.com",
		L"4timonomit4@gmail.com"
	};

	DP::DataPlugin* dp{ nullptr };

public:
	Plugin()
	{
		cout << GWU::console_success;
		cout << "<DataPlugin:Plugin:Plugin>Info: DataPlugin Created." << endl;
		cout << GWU::console_default;
	}
	~Plugin()
	{
		cout << "<DataPlugin:Plugin:Plugin>Info: DataPlugin destroyed." << endl;
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
		#ifdef _DEBUG
		if (dp != nullptr)
		{
			cout << GWU::console_error;
			cout << "<DataPlugin:Plugin:enable>Error: Attempt to re-create the plugin." << endl;
			cout << GWU::console_default;
			return true;
		}
		#endif // _DEBUG

		dp = new DP::DataPlugin;
		cout << GWU::console_success;
		cout << "<DataPlugin:Plugin:enable>Info: enable." << endl;
		cout << GWU::console_default;
		return true;
	};
	bool disableModule() final 
	{
		delete dp;
		dp = nullptr;
		cout << GWU::console_success;
		cout << "<DataPlugin:Plugin:disable>Info: disable." << endl;
		cout << GWU::console_default;
		return true;
	};
};

Plugin* plugin{ nullptr };

extern "C" __declspec(dllexport) GWU::Plugins::Plugin * GetMainClass()
{
	cout << "<DataPlugin:GetMainClass>Info: Called." << endl;
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
		{
			cout << GWU::console_error;
			wcout << "<DataPlugin:DllMain>Error: The main class has been created." << endl;
			cout << GWU::console_default;
		}
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		delete plugin;
		break;
	}
	return TRUE;
}

