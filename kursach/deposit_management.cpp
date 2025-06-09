#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <stdexcept>
#include "header.h" // Оставляем только этот заголовок

using namespace std;

// Загрузка вкладов из файла Deposits.txt
void BankSystem::loadDeposits() {
    ifstream file("Deposits.txt");
    if (!file.is_open()) {
        cout << "Файл Deposits.txt не найден. Будет создан новый файл при сохранении.\n";
        return;
    }
    depositsCount = 0;
    delete[] deposits;
    depositsCapacity = 5;
    deposits = new Deposit[depositsCapacity];
    if (!deposits) {
        file.close();
        throw runtime_error("Ошибка выделения памяти для вкладов в loadDeposits");
    }

    string s, n;
    float a;
    int d, m, y, id;
    while (file >> s >> n >> a >> d >> m >> y >> id) {
        if (depositsCount == depositsCapacity) {
            depositsCapacity += 5;
            Deposit* temp = new Deposit[depositsCapacity];
            if (!temp) {
                file.close();
                delete[] deposits;
                throw runtime_error("Ошибка выделения памяти при расширении массива вкладов");
            }
            for (int i = 0; i < depositsCount; i++) {
                temp[i] = deposits[i];
            }
            delete[] deposits;
            deposits = temp;
        }
        deposits[depositsCount] = Deposit(s, n, a, d, m, y, id);
        depositsCount++;
    }
    file.close();
}

// Сохранение вкладов в файл Deposits.txt
void BankSystem::saveDeposits() {
    ofstream file("Deposits.txt");
    if (!file.is_open()) {
        return;
    }
    for (int i = 0; i < depositsCount; i++) {
        file << deposits[i].getSurname() << " " << deposits[i].getName() << " "
             << deposits[i].getAmount() << " " << deposits[i].getDay() << " "
             << deposits[i].getMonth() << " " << deposits[i].getYear() << " "
             << deposits[i].getDepositId() << endl;
    }
    file.close();
}

// Отображение списка вкладов
void BankSystem::showDeposits() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }
    cout << "Список вкладов:\n";
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() && (deposits[i].getSurname() != currentUser->getSurname() ||
                                        deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        cout << "ID: " << deposits[i].getDepositId() << " | "
             << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
             << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
             << deposits[i].getMonth() << "." << deposits[i].getYear() << endl;
    }
}

// Добавление нового вклада
void BankSystem::addDeposit() {
    if (!currentUser) {
        cout << "Сначала войдите в систему!\n";
        return;
    }

    float a;
    int d, m, y, id;
    string input;

    string s, n;
    if (currentUser->isAdmin()) {
        while (true) {
            cout << "Фамилия: ";
            getline(cin, s);
            if (s.empty()) {
                cout << "Фамилия не может быть пустой. Попробуйте снова." << endl;
                continue;
            }
            bool valid = true;
            for (char c : s) {
                if (!isalpha(c) && c != '-') {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << "Фамилия должна содержать только буквы (и возможный дефис)." << endl;
                continue;
            }
            break;
        }

        while (true) {
            cout << "Имя: ";
            getline(cin, n);
            if (n.empty()) {
                cout << "Имя не может быть пустым. Попробуйте снова." << endl;
                continue;
            }
            bool valid = true;
            for (char c : n) {
                if (!isalpha(c) && c != '-') {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << "Имя должно содержать только буквы (и возможный дефис)." << endl;
                continue;
            }
            break;
        }
    } else {
        s = currentUser->getSurname();
        n = currentUser->getName();
    }

    while (true) {
        cout << "Сумма: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Сумма не может быть пустой. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        if (input.size() == 1 && input[0] == '0') {
            cout << "Сумма не может быть 0." << endl;
            continue;
        }
        try {
            a = stof(input);
            if (a <= 0) {
                cout << "Сумма должна быть больше 0." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Год: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Год не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            y = stoi(input);
            if (y < 2000 || y > 2100) {
                cout << "Год должен быть от 2000 до 2100." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Месяц: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Месяц не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            m = stoi(input);
            if (m < 1 || m > 12) {
                cout << "Месяц должен быть от 1 до 12." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "День: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "День не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            d = stoi(input);
            int maxDays = getDaysInMonth(m, y);
            if (d < 1 || d > maxDays) {
                cout << "В " << m << "-м месяце " << y << " года " << maxDays << " дней. Введите день от 1 до " << maxDays << "." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "ID вклада: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "ID не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            id = stoi(input);
            if (id < 0) {
                cout << "ID не может быть отрицательным." << endl;
                continue;
            }
            for (int i = 0; i < depositsCount; i++) {
                if (deposits[i].getDepositId() == id) {
                    cout << "ID " << id << " уже занят. Введите другой ID." << endl;
                    numer = false;
                    break;
                }
            }
            if (!numer) {
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    if (depositsCount == depositsCapacity) {
        depositsCapacity += 5;
        Deposit* temp = new Deposit[depositsCapacity];
        if (!temp) {
            throw runtime_error("Ошибка выделения памяти при расширении массива вкладов");
        }
        for (int i = 0; i < depositsCount; i++) {
            temp[i] = deposits[i];
        }
        delete[] deposits;
        deposits = temp;
    }

    deposits[depositsCount] = Deposit(s, n, a, d, m, y, id);
    depositsCount++;
    saveDeposits();
    cout << "Вклад добавлен!\n";
}

// Редактирование вклада
void BankSystem::editDeposit() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    showDeposits();
    cout << "Введите ID вклада для редактирования: ";
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
            cout << "Вы можете редактировать только свои вклады!\n";
        } else {
            cout << "Вклад с таким ID не найден.\n";
        }
        return;
    }

    float newAmount;
    int newDay, newMonth, newYear;
    string newSurname = deposits[index].getSurname();
    string newName = deposits[index].getName();
    cout << "Редактирование вклада ID " << id << endl;

    while (true) {
        cout << "Новая сумма: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Сумма не может быть пустой. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            newAmount = stof(input);
            if (newAmount <= 0) {
                cout << "Сумма должна быть больше 0." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Новый год: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Год не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            newYear = stoi(input);
            if (newYear < 2000 || newYear > 2100) {
                cout << "Год должен быть от 2000 до 2100." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Новый месяц: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Месяц не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            newMonth = stoi(input);
            if (newMonth < 1 || newMonth > 12) {
                cout << "Месяц должен быть от 1 до 12." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    while (true) {
        cout << "Новый день: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "День не может быть пустым. Попробуйте снова." << endl;
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
            cout << "Это не число, пожалуйста введите число." << endl;
            continue;
        }
        try {
            newDay = stoi(input);
            int maxDays = getDaysInMonth(newMonth, newYear);
            if (newDay < 1 || newDay > maxDays) {
                cout << "В " << newMonth << "-м месяце " << newYear << " года " << maxDays << " дней. Введите день от 1 до " << maxDays << "." << endl;
                continue;
            }
        } catch (...) {
            cout << "Ошибка преобразования числа." << endl;
            continue;
        }
        break;
    }

    deposits[index] = Deposit(newSurname, newName, newAmount, newDay, newMonth, newYear, id);
    saveDeposits();
    cout << "Вклад отредактирован!\n";
}

// Удаление вклада
void BankSystem::deleteDeposit() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    showDeposits();
    cout << "Введите ID вклада для удаления: ";
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
            cout << "Вы можете удалять только свои вклады!\n";
        } else {
            cout << "Вклад с таким ID не найден.\n";
        }
        return;
    }

    for (int i = index; i < depositsCount - 1; i++) {
        deposits[i] = deposits[i + 1];
    }
    depositsCount--;

    saveDeposits();
    cout << "Вклад удалён!\n";
}