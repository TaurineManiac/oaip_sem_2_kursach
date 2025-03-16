

#ifdef _WIN32
#include <windows.h>
#endif
#include "header.h"
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8 для Windows
#else
    cout << "\033[1;1H"; // Очищаем консоль (опционально)
#endif

    BankSystem bank;
    bank.start();
    return 0;
}