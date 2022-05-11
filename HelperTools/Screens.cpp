#include <Windows.h>
#include "Screens.hpp"
#include <iostream>

using namespace std;

struct cMonitorsVec
{
	std::vector<HMONITOR>  hMonitors;
	std::vector<HDC>       hdcMonitors;
	std::vector<RECT>      rcMonitors;

	static BOOL CALLBACK MonitorEnum(HMONITOR hMon, HDC hdc, LPRECT lprcMonitor, LPARAM pData)
	{
		cMonitorsVec* pThis = reinterpret_cast<cMonitorsVec*>(pData);

		pThis->hMonitors.push_back(hMon);
		pThis->hdcMonitors.push_back(hdc);
		pThis->rcMonitors.push_back(*lprcMonitor);
		return TRUE;
	}

	cMonitorsVec()
	{
		EnumDisplayMonitors(0, 0, MonitorEnum, (LPARAM)this);
	}
};

std::vector<GWU::Screen> GWU::GetScreens()
{
	std::vector<GWU::Screen> v;
	cMonitorsVec Monitors;

	for (int monitorIndex = 0; monitorIndex < Monitors.hdcMonitors.size(); monitorIndex++)
	{
		Screen s;
		s.pos_x = Monitors.rcMonitors[monitorIndex].left;
		s.pos_y = Monitors.rcMonitors[monitorIndex].top;
		
		s.size_x = std::abs(Monitors.rcMonitors[monitorIndex].right - Monitors.rcMonitors[monitorIndex].left);
		s.size_y = std::abs(Monitors.rcMonitors[monitorIndex].top - Monitors.rcMonitors[monitorIndex].bottom);

		v.push_back(s);
	}

	return v;
}
