#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <cmath> // Для abs() в searchByAmount()
#include "header.h" // Оставляем только этот заголовок

using namespace std;

// Поиск вкладов по фамилии (только для администратора)
void BankSystem::searchBySurname() {
    if (!currentUser->isAdmin()) {
        cout << "Ошибка: поиск по фамилии доступен только администратору.\n";
        return;
    }

    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    string surname, input;

    cout << "Введите фамилию для поиска: ";
    while (true) {
        getline(cin, input);
        if (input.empty()) {
            cout << "Фамилия не может быть пустой. Попробуйте снова.\n";
            continue;
        }
        bool provrkaIsAlpha = true;
        for (int i = 0; i < input.size(); i++) {
            if (!isalpha(input[i]) && input[i] != '-') {
                provrkaIsAlpha = false;
                break;
            }
        }
        if (!provrkaIsAlpha) {
            cout << "Фамилия должна содержать только буквы (и возможный дефис). Введите снова.\n";
            continue;
        }
        surname = input;
        break;
    }

    bool found = false;
    cout << "Найденные вклады:\n";
    for (int i = 0; i < depositsCount; i++) {
        string depositSurname = deposits[i].getSurname();
        if (depositSurname == surname) {
            cout << "ID: " << deposits[i].getDepositId() << " | "
                 << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                 << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                 << deposits[i].getMonth() << "." << deposits[i].getYear() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Вклады не найдены.\n";
    }
}

// Поиск вкладов по ID
void BankSystem::searchByID() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    showDeposits();
    cout << "Введите ID вклада для поиска: ";
    string input;
    int id;

    getline(cin, input);
    try {
        id = stoi(input);
    } catch (...) {
        cout << "Некорректный ID.\n";
        return;
    }

    int index = -1;
    bool foundOtherUserDeposit = false;
    for (int i = 0; i < depositsCount; i++) {
        if (deposits[i].getDepositId() == id) {
            if (currentUser->isAdmin()) {
                index = i;
                break;
            } else {
                if (deposits[i].getSurname() == currentUser->getSurname() &&
                    deposits[i].getName() == currentUser->getName()) {
                    index = i;
                    break;
                } else {
                    foundOtherUserDeposit = true;
                }
            }
        }
    }

    if (index == -1) {
        if (foundOtherUserDeposit) {
            cout << "Вы можете просматривать только свои вклады!\n";
        } else {
            cout << "Вклад с таким ID не найден.\n";
        }
        return;
    }

    cout << "Найден вклад:\n";
    cout << "ID: " << deposits[index].getDepositId() << " | "
         << deposits[index].getSurname() << " " << deposits[index].getName() << ", "
         << deposits[index].getAmount() << " руб., дата: " << deposits[index].getDay() << "."
         << deposits[index].getMonth() << "." << deposits[index].getYear() << endl;
}

// Поиск вкладов по сумме
void BankSystem::searchByAmount() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    cout << "Введите сумму для поиска: ";
    string input;
    float amount;

    getline(cin, input);
    if (input.empty()) {
        cout << "Сумма не может быть пустой.\n";
        return;
    }
    bool numer = true;
    int dotcount = 0;
    for (int j = 0; j < input.size(); j++) {
        if (!isdigit(input[j]) && input[j] != '.') {
            numer = false;
            break;
        }
        if (input[j] == '.') {
            dotcount++;
        }
        if (dotcount > 1) {
            numer = false;
            break;
        }
    }
    if (!numer) {
        cout << "Это не число, пожалуйста введите число.\n";
        return;
    }
    try {
        amount = stof(input);
        if (amount <= 0) {
            cout << "Сумма должна быть больше 0.\n";
            return;
        }
    } catch (...) {
        cout << "Ошибка преобразования числа.\n";
        return;
    }

    bool found = false;
    cout << "Найденные вклады:\n";
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        if (abs(deposits[i].getAmount() - amount) < 0.01) {
            cout << "ID: " << deposits[i].getDepositId() << " | "
                 << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                 << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                 << deposits[i].getMonth() << "." << deposits[i].getYear() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Вклады не найдены.\n";
    }
}

// Поиск вкладов по дате
void BankSystem::searchByDate() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    string input;
    int day, month, year;

    while (true) {
        cout << "Введите год: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Год не может быть пустым.\n";
            continue;
        }
        bool numer = true;
        for (int j = 0; j < input.size(); j++) {
            if (!isdigit(input[j])) {
                numer = false;
                break;
            }
        }
        if (!numer) {
            cout << "Это не число, пожалуйста введите число.\n";
            continue;
        }
        try {
            year = stoi(input);
            if (year < 2000 || year > 2100) {
                cout << "Год должен быть от 2000 до 2100.\n";
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Введите месяц: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Месяц не может быть пустым.\n";
            continue;
        }
        bool numer = true;
        for (int j = 0; j < input.size(); j++) {
            if (!isdigit(input[j])) {
                numer = false;
                break;
            }
        }
        if (!numer) {
            cout << "Это не число, пожалуйста введите число.\n";
            continue;
        }
        try {
            month = stoi(input);
            if (month < 1 || month > 12) {
                cout << "Месяц должен быть от 1 до 12.\n";
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Введите день: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "День не может быть пустым.\n";
            continue;
        }
        bool numer = true;
        for (int j = 0; j < input.size(); j++) {
            if (!isdigit(input[j])) {
                numer = false;
                break;
            }
        }
        if (!numer) {
            cout << "Это не число, пожалуйста введите число.\n";
            continue;
        }
        try {
            day = stoi(input);
            int maxDays = getDaysInMonth(month, year);
            if (day < 1 || day > maxDays) {
                cout << "В " << month << "-м месяце " << year << " года " << maxDays << " дней. Введите день от 1 до " << maxDays << ".\n";
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа.\n";
            continue;
        }
        break;
    }

    bool found = false;
    cout << "Найденные вклады:\n";
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        if (deposits[i].getDay() == day &&
            deposits[i].getMonth() == month &&
            deposits[i].getYear() == year) {
            cout << "ID: " << deposits[i].getDepositId() << " | "
                 << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                 << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                 << deposits[i].getMonth() << "." << deposits[i].getYear() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Вклады не найдены.\n";
    }
}

// Фильтрация вкладов по сумме
void BankSystem::filterByAmount() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    float minAmount, maxAmount;
    string input;

    while (true) {
        cout << "Введите минимальную сумму: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Сумма не может быть пустой.\n";
            continue;
        }
        bool numer = true;
        int dotcount = 0;
        for (int j = 0; j < input.size(); j++) {
            if (!isdigit(input[j]) && input[j] != '.') {
                numer = false;
                break;
            }
            if (input[j] == '.') {
                dotcount++;
            }
            if (dotcount > 1) {
                numer = false;
                break;
            }
        }
        if (!numer) {
            cout << "Это не число, пожалуйста введите число.\n";
            continue;
        }
        try {
            minAmount = stof(input);
            if (minAmount <= 0) {
                cout << "Сумма должна быть больше 0.\n";
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Введите максимальную сумму: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Сумма не может быть пустой.\n";
            continue;
        }
        bool numer = true;
        int dotcount = 0;
        for (int j = 0; j < input.size(); j++) {
            if (!isdigit(input[j]) && input[j] != '.') {
                numer = false;
                break;
            }
            if (input[j] == '.') {
                dotcount++;
            }
            if (dotcount > 1) {
                numer = false;
                break;
            }
        }
        if (!numer) {
            cout << "Это не число, пожалуйста введите число.\n";
            continue;
        }
        try {
            maxAmount = stof(input);
            if (maxAmount <= 0) {
                cout << "Сумма должна быть больше 0.\n";
                continue;
            }
            if (maxAmount < minAmount) {
                cout << "Максимальная сумма должна быть больше или равна минимальной.\n";
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа.\n";
            continue;
        }
        break;
    }

    bool found = false;
    cout << "Вклады в диапазоне от " << minAmount << " до " << maxAmount << " руб.:\n";
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        float amount = deposits[i].getAmount();
        if (amount >= minAmount && amount <= maxAmount) {
            cout << "ID: " << deposits[i].getDepositId() << " | "
                 << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                 << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                 << deposits[i].getMonth() << "." << deposits[i].getYear() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Вклады не найдены.\n";
    }
}

// Показ новых вкладов за текущий месяц
void BankSystem::showNewThisMonth() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    int currentMonth = 3; // Март (по текущей дате)
    int currentYear = 2025;

    bool found = false;
    cout << "Вклады за март 2025 года:\n";
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        if (deposits[i].getMonth() == currentMonth && deposits[i].getYear() == currentYear) {
            cout << "ID: " << deposits[i].getDepositId() << " | "
                 << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                 << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                 << deposits[i].getMonth() << "." << deposits[i].getYear() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Вклады за этот месяц не найдены.\n";
    }
}