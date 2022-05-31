#include <algorithm>
#include <iostream>
#include <Windows.h>

#include "DataPlugin.hpp"
#include "../HelperTools/Console.hpp"

using namespace std;

DP::DataPlugin::DataPlugin()
{
	registerValue(L"CpuUsage", Value::Tupe::Percent, [this](Value* v) -> bool
		{
			return cpuUsage(v);
		});

	cout << GWU::console_success;
	cout << "<DP:DataPlugin:DataPlugin>Info: Created." << endl;
	cout << GWU::console_default;
}
DP::DataPlugin::~DataPlugin()
{
	for (auto e : elements)
		delete e;
	elements.clear();
}

DP::DataPlugin::FunkValueId DP::DataPlugin::registerValue(sf::String name, Value::Tupe tupe, CallbackF f)
{
	auto find_pos = find_if(elements.begin(), elements.end(), [&name, &tupe, &f](const Element* e) { return e->name == name && e->t == tupe; });
	if (find_pos != elements.end())
		return nullptr;//Such handler is already registered.

	Element* e = new Element;
	e->name = name;
	e->t = tupe;
	e->f = f;
	elements.push_back(e);

	return e;
}
bool DP::DataPlugin::unregisterValue(FunkValueId id)
{
	auto find = std::find(elements.begin(), elements.end(), id);
	if (find == elements.end())
		return false; // Not found

	auto el = *find;
	delete el;
	elements.erase(find);

	return true;
}

static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;


	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

	_previousTotalTicks = totalTicks;
	_previousIdleTicks = idleTicks;
	return ret;
}
static unsigned long long FileTimeToInt64(const FILETIME& ft)
{
	return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
float GetCPULoad()
{
	FILETIME idleTime, kernelTime, userTime;
	return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}
bool DP::DataPlugin::cpuUsage(Value* v)
{
	if (v->t != Value::Tupe::Percent)
		return false;

	Percent* p = reinterpret_cast<Percent*>(v);
	p->v = GetCPULoad();

	return true;
}