#pragma once
#ifdef KERNEL_EXPORTS
#define GWU_EXPORT __declspec(dllexport)
#else
#define GWU_EXPORT __declspec(dllimport)
#pragma comment(lib,"Kernel.lib")
#endif

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
//#ifdef _MSC_VER
//#pragma warning(disable: 4251)
//#endif