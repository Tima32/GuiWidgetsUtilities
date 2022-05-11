// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <windows.h>
#include <iostream>
#include "ImportExport.hpp"

using namespace std;

class GWU_EXPORT Info
{

};

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	static size_t i{ 0 };
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		i++;
		cout << "Kernel attach: " << i << endl;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

