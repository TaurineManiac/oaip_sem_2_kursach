#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include <algorithm>
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
        }
        else {
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
Deposit::Deposit(string s, string n, float a, int d, int m, int y, int id) {
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

float Deposit::getAmount() const {
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
    users = new User * [userCapacity];
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
    loadDeposits();

    users[countUsers] = new Admin("admin", "admin123", "Admin", "Admin");
    if (!users[countUsers]) {
        delete[] users;
        delete[] deposits;
        throw runtime_error("Ошибка создания администратора");
    }
    countUsers++;
}

// Деструктор класса BankSystem
BankSystem::~BankSystem() {
    delete[] deposits;
    deposits = nullptr;
    for (int i = 0; i < countUsers; i++) {
        delete users[i];
        users[i] = nullptr;
    }
    delete[] users;
    users = nullptr;
}

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
            }
            else {
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
            }
            else {
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
        User** temp = new User * [userCapacity];
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
    }
    else {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
    }
    catch (...) {
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
            }
            else {
                if (deposits[i].getSurname() == currentUser->getSurname() &&
                    deposits[i].getName() == currentUser->getName()) {
                    index = i;
                    break;
                }
                else {
                    foundOtherUserDeposit = true;
                }
            }
        }
    }

    if (index == -1) {
        if (foundOtherUserDeposit) {
            cout << "Вы можете редактировать только свои вклады!\n";
        }
        else {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
    }
    catch (...) {
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
            }
            else {
                if (deposits[i].getSurname() == currentUser->getSurname() &&
                    deposits[i].getName() == currentUser->getName()) {
                    index = i;
                    break;
                }
                else {
                    foundOtherUserDeposit = true;
                }
            }
        }
    }

    if (index == -1) {
        if (foundOtherUserDeposit) {
            cout << "Вы можете удалять только свои вклады!\n";
        }
        else {
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
    }
    catch (...) {
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
            }
            else {
                if (deposits[i].getSurname() == currentUser->getSurname() &&
                    deposits[i].getName() == currentUser->getName()) {
                    index = i;
                    break;
                }
                else {
                    foundOtherUserDeposit = true;
                }
            }
        }
    }

    if (index == -1) {
        if (foundOtherUserDeposit) {
            cout << "Вы можете просматривать только свои вклады!\n";
        }
        else {
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
    }
    catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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
        }
        catch (...) {
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

// Сортировка вкладов по фамилии (только для администратора)
void BankSystem::sortBySurname() {
    if (!currentUser->isAdmin()) {
        cout << "Ошибка: сортировка по фамилии доступна только администратору.\n";
        return;
    }

    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    for (int i = 0; i < depositsCount - 1; i++) {
        for (int j = 0; j < depositsCount - i - 1; j++) {
            if (deposits[j].getSurname() > deposits[j + 1].getSurname()) {
                Deposit temp = deposits[j];
                deposits[j] = deposits[j + 1];
                deposits[j + 1] = temp;
            }
        }
    }

    cout << "Вклады отсортированы по фамилии.\n";
    showDeposits();
    saveDeposits();
}

// Сортировка вкладов по ID
void BankSystem::sortByID() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    if (currentUser->isAdmin()) {
        for (int i = 0; i < depositsCount - 1; i++) {
            for (int j = 0; j < depositsCount - i - 1; j++) {
                if (deposits[j].getDepositId() > deposits[j + 1].getDepositId() ||
                    (deposits[j].getDepositId() == deposits[j + 1].getDepositId() &&
                     deposits[j].getSurname() > deposits[j + 1].getSurname())) {
                    Deposit temp = deposits[j];
                    deposits[j] = deposits[j + 1];
                    deposits[j + 1] = temp;
                }
            }
        }
        cout << "Вклады отсортированы по ID.\n";
        showDeposits();
        saveDeposits();
    }
    else {
        bool swapped;
        for (int i = 0; i < depositsCount - 1; i++) {
            swapped = false;
            for (int j = 0; j < depositsCount - i - 1; j++) {
                bool jIsUser = (deposits[j].getSurname() == currentUser->getSurname() &&
                                deposits[j].getName() == currentUser->getName());
                bool jPlus1IsUser = (deposits[j + 1].getSurname() == currentUser->getSurname() &&
                                     deposits[j + 1].getName() == currentUser->getName());

                if (jIsUser && jPlus1IsUser) {
                    if (deposits[j].getDepositId() > deposits[j + 1].getDepositId() ||
                        (deposits[j].getDepositId() == deposits[j + 1].getDepositId() &&
                         deposits[j].getSurname() > deposits[j + 1].getSurname())) {
                        Deposit temp = deposits[j];
                        deposits[j] = deposits[j + 1];
                        deposits[j + 1] = temp;
                        swapped = true;
                    }
                }
            }
            if (!swapped) break;
        }
        cout << "Ваши вклады отсортированы по ID.\n";
        showDeposits();
        saveDeposits();
    }
}

// Сортировка вкладов по сумме
void BankSystem::sortByAmount() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    if (currentUser->isAdmin()) {
        for (int i = 0; i < depositsCount - 1; i++) {
            for (int j = 0; j < depositsCount - i - 1; j++) {
                if (deposits[j].getAmount() > deposits[j + 1].getAmount()) {
                    Deposit temp = deposits[j];
                    deposits[j] = deposits[j + 1];
                    deposits[j + 1] = temp;
                }
            }
        }
        cout << "Вклады отсортированы по сумме.\n";
        showDeposits();
        saveDeposits();
    }
    else {
        bool swapped;
        for (int i = 0; i < depositsCount - 1; i++) {
            swapped = false;
            for (int j = 0; j < depositsCount - i - 1; j++) {
                bool jIsUser = (deposits[j].getSurname() == currentUser->getSurname() &&
                                deposits[j].getName() == currentUser->getName());
                bool jPlus1IsUser = (deposits[j + 1].getSurname() == currentUser->getSurname() &&
                                     deposits[j + 1].getName() == currentUser->getName());

                if (jIsUser && jPlus1IsUser) {
                    if (deposits[j].getAmount() > deposits[j + 1].getAmount()) {
                        Deposit temp = deposits[j];
                        deposits[j] = deposits[j + 1];
                        deposits[j + 1] = temp;
                        swapped = true;
                    }
                }
            }
            if (!swapped) break;
        }
        cout << "Ваши вклады отсортированы по сумме.\n";
        showDeposits();
        saveDeposits();
    }
}

// Сортировка вкладов по дате
void BankSystem::sortByDate() {
    if (depositsCount == 0) {
        cout << "Вкладов нет.\n";
        return;
    }

    if (currentUser->isAdmin()) {
        for (int i = 0; i < depositsCount - 1; i++) {
            for (int j = 0; j < depositsCount - i - 1; j++) {
                if (deposits[j].getYear() > deposits[j + 1].getYear() ||
                    (deposits[j].getYear() == deposits[j + 1].getYear() &&
                     deposits[j].getMonth() > deposits[j + 1].getMonth()) ||
                    (deposits[j].getYear() == deposits[j + 1].getYear() &&
                     deposits[j].getMonth() == deposits[j + 1].getMonth() &&
                     deposits[j].getDay() > deposits[j + 1].getDay())) {
                    Deposit temp = deposits[j];
                    deposits[j] = deposits[j + 1];
                    deposits[j + 1] = temp;
                }
            }
        }
        cout << "Вклады отсортированы по дате.\n";
        showDeposits();
        saveDeposits();
    }
    else {
        bool swapped;
        for (int i = 0; i < depositsCount - 1; i++) {
            swapped = false;
            for (int j = 0; j < depositsCount - i - 1; j++) {
                bool jIsUser = (deposits[j].getSurname() == currentUser->getSurname() &&
                                deposits[j].getName() == currentUser->getName());
                bool jPlus1IsUser = (deposits[j + 1].getSurname() == currentUser->getSurname() &&
                                     deposits[j + 1].getName() == currentUser->getName());

                if (jIsUser && jPlus1IsUser) {
                    if (deposits[j].getYear() > deposits[j + 1].getYear() ||
                        (deposits[j].getYear() == deposits[j + 1].getYear() &&
                         deposits[j].getMonth() > deposits[j + 1].getMonth()) ||
                        (deposits[j].getYear() == deposits[j + 1].getYear() &&
                         deposits[j].getMonth() == deposits[j + 1].getMonth() &&
                         deposits[j].getDay() > deposits[j + 1].getDay())) {
                        Deposit temp = deposits[j];
                        deposits[j] = deposits[j + 1];
                        deposits[j + 1] = temp;
                        swapped = true;
                    }
                }
            }
            if (!swapped) break;
        }
        cout << "Ваши вклады отсортированы по дате.\n";
        showDeposits();
        saveDeposits();
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
            break; // брейк для додиков
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
        }
        else {
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
    cout << "Пользователь и его вклады удалены.\n";
}

// Меню администратора
void BankSystem::adminMenu() {
    string choice;
    while (true) {
        cout << "\nМеню администратора:\n";
        cout << "1. Добавить вклад\n";
        cout << "2. Редактировать вклад\n";
        cout << "3. Удалить вклад\n";
        cout << "4. Показать все вклады\n";
        cout << "5. Поиск по фамилии\n";
        cout << "6. Поиск по ID\n";
        cout << "7. Поиск по сумме\n";
        cout << "8. Поиск по дате\n";
        cout << "9. Фильтровать по сумме\n";
        cout << "10. Сортировать по фамилии\n";
        cout << "11. Сортировать по ID\n";
        cout << "12. Сортировать по сумме\n";
        cout << "13. Сортировать по дате\n";
        cout << "14. Показать новые вклады за месяц\n";
        cout << "15. Удалить пользователя\n";
        cout << "16. Зарегистрировать нового пользователя\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        getline(cin, choice);

        if (choice == "0") {
            break;
        }
        else if (choice == "1") {
            addDeposit();
        }
        else if (choice == "2") {
            editDeposit();
        }
        else if (choice == "3") {
            deleteDeposit();
        }
        else if (choice == "4") {
            showDeposits();
        }
        else if (choice == "5") {
            searchBySurname();
        }
        else if (choice == "6") {
            searchByID();
        }
        else if (choice == "7") {
            searchByAmount();
        }
        else if (choice == "8") {
            searchByDate();
        }
        else if (choice == "9") {
            filterByAmount();
        }
        else if (choice == "10") {
            sortBySurname();
        }
        else if (choice == "11") {
            sortByID();
        }
        else if (choice == "12") {
            sortByAmount();
        }
        else if (choice == "13") {
            sortByDate();
        }
        else if (choice == "14") {
            showNewThisMonth();
        }
        else if (choice == "15") {
            deleteUser();
        }
        else if (choice == "16") {
            registerUser();
        }
        else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

// Меню пользователя
void BankSystem::userMenu() {
    string choice;
    while (true) {
        cout << "\nМеню пользователя:\n";
        cout << "1. Добавить вклад\n";
        cout << "2. Редактировать вклад\n";
        cout << "3. Удалить вклад\n";
        cout << "4. Показать мои вклады\n";
        cout << "5. Поиск по ID\n";
        cout << "6. Поиск по сумме\n";
        cout << "7. Поиск по дате\n";
        cout << "8. Фильтровать по сумме\n";
        cout << "9. Сортировать по ID\n";
        cout << "10. Сортировать по сумме\n";
        cout << "11. Сортировать по дате\n";
        cout << "12. Показать новые вклады за последний месяц\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        getline(cin, choice);

        if (choice == "0") {
            break;
        }
        else if (choice == "1") {
            addDeposit();
        }
        else if (choice == "2") {
            editDeposit();
        }
        else if (choice == "3") {
            deleteDeposit();
        }
        else if (choice == "4") {
            showDeposits();
        }
        else if (choice == "5") {
            searchByID();
        }
        else if (choice == "6") {
            searchByAmount();
        }
        else if (choice == "7") {
            searchByDate();
        }
        else if (choice == "8") {
            filterByAmount();
        }
        else if (choice == "9") {
            sortByID();
        }
        else if (choice == "10") {
            sortByAmount();
        }
        else if (choice == "11") {
            sortByDate();
        }
        else if (choice == "12") {
            showNewThisMonth();
        }
        else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}

// Запуск программы
void BankSystem::start() {
    string choice;
    while (true) {
        cout << "\nБанковская система\n";
        cout << "1. Войти\n";
        cout << "2. Зарегистрироваться\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        getline(cin, choice);

        if (choice == "0") {
            break;
        }
        else if (choice == "1") {
            if (logIn()) {
                if (currentUser->isAdmin()) {
                    adminMenu();
                }
                else {
                    userMenu();
                }
            }
        }
        else if (choice == "2") {
            registerUser();
        }
        else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}