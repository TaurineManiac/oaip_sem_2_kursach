#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <stdexcept>
#include "header.h" // Оставляем только этот заголовок

using namespace std;

// Загрузка пользователей из файла Users.txt
void BankSystem::loadUsers() {
    ifstream file("Users.txt");
    if (!file.is_open()) {
        cout << "Файл Users.txt не найден. Создаётся новый файл.\n";
        return;
    }

    // Очищаем текущий массив пользователей (кроме администратора, который создаётся в конструкторе)
    for (int i = 1; i < countUsers; i++) { // Начинаем с 1, чтобы не удалять администратора
        delete users[i];
        users[i] = nullptr;
    }
    countUsers = 1; // Оставляем только администратора (он уже создан в конструкторе)

    string username, password, surname, name;
    int isAdmin;
    while (file >> username >> password >> surname >> name >> isAdmin) {
        if (username == "admin") {
            continue; // Пропускаем администратора, так как он уже создан в конструкторе
        }

        if (countUsers == userCapacity) {
            userCapacity += 2;
            User** temp = new User*[userCapacity];
            if (!temp) {
                file.close();
                throw runtime_error("Ошибка выделения памяти при расширении массива пользователей в loadUsers");
            }
            for (int i = 0; i < countUsers; i++) {
                temp[i] = users[i];
            }
            for (int i = countUsers; i < userCapacity; i++) {
                temp[i] = nullptr;
            }
            delete[] users;
            users = temp;
        }

        if (isAdmin == 1) {
            users[countUsers] = new Admin(username, password, surname, name);
        } else {
            users[countUsers] = new RegularUser(username, password, surname, name);
        }
        if (!users[countUsers]) {
            file.close();
            throw runtime_error("Ошибка создания пользователя при загрузке из файла");
        }
        countUsers++;
    }
    file.close();
}

// Сохранение пользователей в файл Users.txt
void BankSystem::saveUsers() {
    ofstream file("Users.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл Users.txt для записи.\n";
        return;
    }

    for (int i = 0; i < countUsers; i++) {
        file << users[i]->getUsername() << " "
             << users[i]->getPassword() << " "
             << users[i]->getSurname() << " "
             << users[i]->getName() << " "
             << (users[i]->isAdmin() ? 1 : 0) << endl;
    }
    file.close();
}

// Авторизация пользователя
bool BankSystem::logIn() {
    cout << "Введите логин и пароль" << endl;
    string login, pass;
    string input;

    while (true) {
        bool proverkaLogIn = false;
        cout << "Введите логин (без пробелов): ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Поле не может быть пустым. Попробуйте снова." << endl;
            continue;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isspace(input[i])) {
                proverkaLogIn = true;
                break;
            }
        }
        if (proverkaLogIn) {
            cout << "Строка содержит пробелы. Попробуйте снова." << endl;
            continue;
        }
        break;
    }
    login = input;

    while (true) {
        bool proverkaLogIn = false;
        cout << "Введите пароль (без пробелов): ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Поле не может быть пустым. Попробуйте снова." << endl;
            continue;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isspace(input[i])) {
                proverkaLogIn = true;
                break;
            }
        }
        if (proverkaLogIn) {
            cout << "Строка содержит пробелы. Попробуйте снова." << endl;
            continue;
        }
        break;
    }
    pass = input;

    for (int i = 0; i < countUsers; i++) {
        if (users[i]->getUsername() == login && users[i]->getPassword() == pass) {
            currentUser = users[i];
            cout << "Вы вошли." << endl;
            return true;
        }
    }
    cout << "Ошибка! Неверный логин или пароль.\n";
    return false;
}

// Регистрация нового пользователя
void BankSystem::registerUser() {
    cout << "Для регистрации введите логин, пароль, имя и фамилию" << endl;
    string login, pass, name, surname;
    string input;

    // Ввод логина
    while (true) {
        bool proverkaLogIn = false;
        cout << "Введите логин (без пробелов): ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Поле не может быть пустым. Попробуйте снова." << endl;
            continue;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isspace(input[i])) {
                proverkaLogIn = true;
                break;
            }
        }
        if (proverkaLogIn) {
            cout << "Строка содержит пробелы. Попробуйте снова." << endl;
            continue;
        }
        if (isUsernameTaken(input)) {
            cout << "Данное имя пользователя уже занято. Попробуйте другое." << endl;
            continue;
        }
        break;
    }
    login = input;

    // Ввод пароля
    while (true) {
        bool proverkaLogIn = false;
        cout << "Введите пароль (без пробелов): ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Поле не может быть пустым. Попробуйте снова." << endl;
            continue;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isspace(input[i])) {
                proverkaLogIn = true;
                break;
            }
        }
        if (proverkaLogIn) {
            cout << "Строка содержит пробелы. Попробуйте снова." << endl;
            continue;
        }
        break;
    }
    pass = input;

    // Ввод имени
    while (true) {
        bool provrkaIsAlpha = false;
        int counterLetter = 0;
        cout << "Введите имя: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Поле не может быть пустым. Попробуйте снова." << endl;
            continue;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isspace(input[i])) {
                provrkaIsAlpha = false;
                break;
            }
            if (isalpha(input[i]) || input[i] == '-') {
                provrkaIsAlpha = true;
                if (isalpha(input[i])) {
                    counterLetter++;
                }
            } else {
                provrkaIsAlpha = false;
                break;
            }
        }
        if (!provrkaIsAlpha || counterLetter == 0) {
            cout << "Имя должно содержать только буквы (и возможный дефис) и не быть пустым." << endl;
            continue;
        }
        name = input;
        break;
    }

    // Ввод фамилии
    while (true) {
        bool provrkaIsAlpha = false;
        int counterLetter = 0;
        cout << "Введите фамилию: ";
        getline(cin, input);
        if (input.empty()) {
            cout << "Поле не может быть пустым. Попробуйте снова." << endl;
            continue;
        }
        for (int i = 0; i < input.size(); i++) {
            if (isspace(input[i])) {
                provrkaIsAlpha = false;
                break;
            }
            if (isalpha(input[i]) || input[i] == '-') {
                provrkaIsAlpha = true;
                if (isalpha(input[i])) {
                    counterLetter++;
                }
            } else {
                provrkaIsAlpha = false;
                break;
            }
        }
        if (!provrkaIsAlpha || counterLetter == 0) {
            cout << "Фамилия должна содержать только буквы (и возможный дефис) и не быть пустой." << endl;
            continue;
        }
        surname = input;
        break;
    }

    if (countUsers == userCapacity) {
        userCapacity += 2;
        User** temp = new User*[userCapacity];
        if (!temp) {
            throw runtime_error("Ошибка выделения памяти при расширении массива пользователей");
        }
        for (int i = 0; i < countUsers; i++) {
            temp[i] = users[i];
        }
        for (int i = countUsers; i < userCapacity; i++) {
            temp[i] = nullptr;
        }
        delete[] users;
        users = temp;
    }

    users[countUsers] = new RegularUser(login, pass, surname, name);
    if (!users[countUsers]) {
        throw runtime_error("Ошибка создания нового пользователя");
    }
    countUsers++;
    cout << "Пользователь зарегистрирован!\n";

    // Сохраняем пользователей в файл
    saveUsers();
}

// Проверка, занят ли логин
bool BankSystem::isUsernameTaken(string login) {
    for (int i = 0; i < countUsers; i++) {
        if (users[i]->getUsername() == login) {
            return true;
        }
    }
    return false;
}

// Удаление пользователя (только для администратора)
void BankSystem::deleteUser() {
    if (!currentUser->isAdmin()) {
        cout << "Ошибка: удаление пользователей доступно только администратору.\n";
        return;
    }

    if (countUsers <= 1) {
        cout << "Нельзя удалить последнего пользователя (администратора).\n";
        return;
    }

    string username;

    cout << "Введите логин пользователя для удаления: ";
    getline(cin, username);

    if (username == "admin") {
        cout << "Нельзя удалить администратора!\n";
        return;
    }

    int userIndex = -1;
    for (int i = 0; i < countUsers; i++) {
        if (users[i]->getUsername() == username) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        cout << "Пользователь с таким логином не найден.\n";
        return;
    }

    int i = 0;
    while (i < depositsCount) {
        if (deposits[i].getSurname() == users[userIndex]->getSurname() &&
            deposits[i].getName() == users[userIndex]->getName()) {
            for (int j = i; j < depositsCount - 1; j++) {
                deposits[j] = deposits[j + 1];
            }
            depositsCount--;
        } else {
            i++;
        }
    }

    delete users[userIndex];
    for (int i = userIndex; i < countUsers - 1; i++) {
        users[i] = users[i + 1];
    }
    users[countUsers - 1] = nullptr;
    countUsers--;

    saveDeposits();
    saveUsers(); // Сохраняем пользователей после удаления
    cout << "Пользователь и его вклады удалены.\n";
}