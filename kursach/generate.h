#ifndef MEGAGENERATE_MEGAGENERATE_H
#define MEGAGENERATE_MEGAGENERATE_H

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#include <string>

namespace generate {
    DLL_EXPORT std::string generateStringIndex();
    DLL_EXPORT int generateRandomNumber(int min,int max);
    DLL_EXPORT std::string generateCurrentDataTime();
    DLL_EXPORT std::string generateRandomString(int max);
}

#endif // MEGAGENERATE_MEGAGENERATE_H