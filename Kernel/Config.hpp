#pragma once
#include <iostream>

#ifdef _WIN32

	auto& wout = std::wcout; //widget out
	auto& win = std::wcin;

//#define TEXT(quote) L##quote

#else
#error "The configuration is not defined."
#endif