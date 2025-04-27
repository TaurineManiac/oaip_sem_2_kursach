#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <windows.h>
#include "header.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    try {
        BankSystem bank;
        bank.start();
    } catch (const std::exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return 1;
    }
    return 0;
}