#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "../Kernel/ImportExport.hpp"
#include "../Kernel/Plugins.hpp"
#include "../HelperTools/Screens.hpp"

using namespace std;
#define out wcout


int MyMain()
{
	FILE* fDummy{};
#ifdef _DEBUG
	AllocConsole();
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "en_EN.UTF-8");
#else
	freopen_s(&fDummy, "log.txt", "w", stdout);
	setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

	out << TEXT("Hello World. I am GUI Widget Utilities. Привет. こんにちは") << endl;

	GWU::Plugins::plugins.loadPlugins();
	GWU::Plugins::plugins.unloadPlugins();

	return 0;
}
//int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	return MyMain();
//}

int main()
{
	return MyMain();
}
