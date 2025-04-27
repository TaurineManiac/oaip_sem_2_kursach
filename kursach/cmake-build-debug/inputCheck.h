#ifndef INPUTCHECK_INPUTCHECK_H
#define INPUTCHECK_INPUTCHECK_H

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#include <string>

namespace mylib {
    DLL_EXPORT int checkYourSolution(int lastNum);
    DLL_EXPORT double checkTryToInputDouble();
    DLL_EXPORT int checkTryToInputMaxSizeOfSmth();
    DLL_EXPORT int checkTryToInputInt();
    DLL_EXPORT int checkTryToInputChar();
    DLL_EXPORT std::string trimInput(const std::string& input);
    DLL_EXPORT std::string checkTryToInputString(bool allowCyrillic = false); // Новая функция для ввода строк

}

#endif // INPUTCHECK_INPUTCHECK_H