#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <stdexcept>
#include "header.h"

using namespace std;

// Загрузка пользователей из файла Users.txt
void BankSystem::loadUsers() {
    ifstream file("Users.txt");
    if (!file.is_open()) {
        cout << "Файл Users.txt не найден. Создаётся новый файл.\n";
        return;
    }

    for (int i = 1; i < countUsers; i++) {
        delete users[i];
        users[i] = nullptr;
    }
    countUsers = 1;

    string username, password, surname, name;
    int isAdmin;
    while (file >> username >> password >> surname >> name >> isAdmin) {
        if (username == "admin") {
            continue;
        }

        if (countUsers == userCapacity) {
            users = expandUsers(users, userCapacity);
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
    cout << "Введите логин: ";
    string login = mylib::checkTryToInputString(false); // Только латиница
    cout << "Введите пароль: ";
    string pass = mylib::checkTryToInputString(false); // Только латиница

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

    string login;
    cout << "Введите логин: ";
    while (true) {
        login = mylib::checkTryToInputString(false); // Только латиница
        if (isUsernameTaken(login)) {
            cout << "Данное имя пользователя уже занято. Попробуйте другое." << endl;
            continue;
        }
        break;
    }

    cout << "Введите пароль: ";
    string pass = mylib::checkTryToInputString(false); // Только латиница

    cout << "Введите имя: ";
    string name = mylib::checkTryToInputString(true); // Разрешаем кириллицу

    cout << "Введите фамилию: ";
    string surname = mylib::checkTryToInputString(true); // Разрешаем кириллицу

    if (countUsers == userCapacity) {
        users = expandUsers(users, userCapacity);
    }

    users[countUsers] = new RegularUser(login, pass, surname, name);
    if (!users[countUsers]) {
        throw runtime_error("Ошибка создания нового пользователя");
    }
    countUsers++;
    cout << "Пользователь зарегистрирован!\n";

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
    for (int i = 0; i < countUsers; i++) {
        cout <<i+1 << ")" <<users[i]->getUsername() << " " ;
        cout << users[i]->getName()<< " " ;
        cout << users[i]->getSurname() << endl;

    }

    if (!currentUser->isAdmin()) {
        cout << "Ошибка: удаление пользователей доступно только администратору.\n";
        return;
    }

    if (countUsers <= 1) {
        cout << "Нельзя удалить последнего пользователя (администратора).\n";
        return;
    }

    cout << "Введите логин пользователя для удаления: ";
    string username = mylib::checkTryToInputString(false); // Только латиница

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

    cout << "Вы уверены что хотите удалить пользователя?" << endl;
    cout << "1- Да\n"
            "2- Нет" << endl;
    int choiceTryToDelete=mylib::checkYourSolution(2);
    if (choiceTryToDelete == 2) {
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
    saveUsers();
    cout << "Пользователь и его вклады удалены.\n";
}

void BankSystem::showUsers() {
    for (int i = 0; i < countUsers; i++) {
        cout <<i+1 << ")" <<users[i]->getUsername() << " " ;
        cout << users[i]->getName()<< " " ;
        cout << users[i]->getSurname() << endl;

    }
}
