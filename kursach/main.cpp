#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "header.h" // Оставляем только этот заголовок

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#else
    cout << "\033[1;1H";
#endif

    BankSystem bank;
    bank.start();
    return 0;
}