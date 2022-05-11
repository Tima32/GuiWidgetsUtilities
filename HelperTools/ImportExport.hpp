#pragma once
#ifdef GWUT_EXPORTS
#define GWUT_EXPORT __declspec(dllexport)
#else
#define GWUT_EXPORT __declspec(dllimport)
#pragma comment(lib,"HelperTools.lib")
#endif

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
//#ifdef _MSC_VER
//#pragma warning(disable: 4251)
//#endif