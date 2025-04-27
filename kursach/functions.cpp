#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "header.h"

using namespace std;

// Функция для проверки високосного года
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Функция для определения количества дней в месяце
int getDaysInMonth(int month, int year) {
    if (month == 2) {
        if (isLeapYear(year)) {
            return 29;
        } else {
            return 28;
        }
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    }
    return 30;
}

// Геттеры класса User
string User::getPassword() {
    return password;
}

string User::getUsername() {
    return username;
}

string User::getSurname() const {
    return surname;
}

string User::getName() const {
    return name;
}

// Конструктор класса User
User::User(string u, string p, string s, string n) {
    username = u;
    password = p;
    surname = s;
    name = n;
}

// Деструктор класса User
User::~User() {
    // Пустой, так как нет динамической памяти
}

// Метод для проверки, является ли пользователь администратором
bool Admin::isAdmin() const {
    return true;
}

// Конструктор класса Admin
Admin::Admin(string u, string p, string s, string n) : User(u, p, s, n) {}

// Метод для проверки, является ли пользователь администратором
bool RegularUser::isAdmin() const {
    return false;
}

// Конструктор класса RegularUser
RegularUser::RegularUser(string u, string p, string s, string n) : User(u, p, s, n) {}

// Конструктор класса Deposit
Deposit::Deposit(string s, string n, double a, int d, int m, int y, int id) {
    surname = s;
    name = n;
    amount = a;
    day = d;
    month = m;
    year = y;
    depositID = id;
}

// Геттеры класса Deposit
string Deposit::getSurname() const {
    return surname;
}

string Deposit::getName() const {
    return name;
}

double Deposit::getAmount() const {
    return amount;
}

int Deposit::getDay() const {
    return day;
}

int Deposit::getMonth() const {
    return month;
}

int Deposit::getYear() const {
    return year;
}

int Deposit::getDepositId() const {
    return depositID;
}

// Конструктор класса BankSystem
BankSystem::BankSystem() {
    countUsers = 0;
    userCapacity = 2;
    users = new User*[userCapacity];
    if (!users) {
        throw runtime_error("Ошибка выделения памяти для пользователей");
    }
    for (int i = 0; i < userCapacity; i++) {
        users[i] = nullptr;
    }
    currentUser = nullptr;
    depositsCount = 0;
    depositsCapacity = 5;
    deposits = new Deposit[depositsCapacity];
    if (!deposits) {
        delete[] users;
        throw runtime_error("Ошибка выделения памяти для вкладов");
    }

    // Создаём администратора
    users[countUsers] = new Admin("admin", "admin123", "Admin", "Admin");
    if (!users[countUsers]) {
        delete[] users;
        delete[] deposits;
        throw runtime_error("Ошибка создания администратора");
    }
    countUsers++;

    // Загружаем пользователей и вклады
    loadUsers();
    loadDeposits();
}

// Деструктор класса BankSystem
BankSystem::~BankSystem() {
    saveUsers(); // Сохраняем пользователей
    saveDeposits(); // Сохраняем вклады
    delete[] deposits;
    deposits = nullptr;
    for (int i = 0; i < countUsers; i++) {
        delete users[i];
        users[i] = nullptr;
    }
    delete[] users;
    users = nullptr;
}