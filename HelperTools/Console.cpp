#include <windows.h>
#include "Console.hpp"

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void GWU::SetConsoleTextColor(ConsoleTextColor color)
{   
    SetConsoleTextAttribute(hConsole, uint16_t(color));
}

namespace GWU
{
    ConsoleT console_default(ConsoleTextColor::Default);
    ConsoleT console_success(ConsoleTextColor::Success);
    ConsoleT console_warning(ConsoleTextColor::Warning);
    ConsoleT console_error(ConsoleTextColor::Error);
}

std::ostream& operator << (std::ostream& os, const GWU::ConsoleT& c)
{
    SetConsoleTextColor(c.c);
    return os;
}