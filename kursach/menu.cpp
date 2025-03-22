#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include "header.h" // Оставляем только этот заголовок

using namespace std;

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
        } else if (choice == "1") {
            addDeposit();
        } else if (choice == "2") {
            editDeposit();
        } else if (choice == "3") {
            deleteDeposit();
        } else if (choice == "4") {
            showDeposits();
        } else if (choice == "5") {
            searchBySurname();
        } else if (choice == "6") {
            searchByID();
        } else if (choice == "7") {
            searchByAmount();
        } else if (choice == "8") {
            searchByDate();
        } else if (choice == "9") {
            filterByAmount();
        } else if (choice == "10") {
            sortBySurname();
        } else if (choice == "11") {
            sortByID();
        } else if (choice == "12") {
            sortByAmount();
        } else if (choice == "13") {
            sortByDate();
        } else if (choice == "14") {
            showNewThisMonth();
        } else if (choice == "15") {
            deleteUser();
        } else if (choice == "16") {
            registerUser();
        } else {
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
        } else if (choice == "1") {
            addDeposit();
        } else if (choice == "2") {
            editDeposit();
        } else if (choice == "3") {
            deleteDeposit();
        } else if (choice == "4") {
            showDeposits();
        } else if (choice == "5") {
            searchByID();
        } else if (choice == "6") {
            searchByAmount();
        } else if (choice == "7") {
            searchByDate();
        } else if (choice == "8") {
            filterByAmount();
        } else if (choice == "9") {
            sortByID();
        } else if (choice == "10") {
            sortByAmount();
        } else if (choice == "11") {
            sortByDate();
        } else if (choice == "12") {
            showNewThisMonth();
        } else {
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
        } else if (choice == "1") {
            if (logIn()) {
                if (currentUser->isAdmin()) {
                    adminMenu();
                } else {
                    userMenu();
                }
            }
        } else if (choice == "2") {
            registerUser();
        } else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}