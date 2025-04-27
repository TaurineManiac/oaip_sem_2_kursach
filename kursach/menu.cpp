#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include "header.h"

using namespace std;

// Меню администратора
void BankSystem::adminMenu() {
    while (true) {
        cout << "\nМеню администратора:\n";
        cout << "1. Добавить вклад\n";
        cout << "2. Редактировать вклад\n";
        cout << "3. Удалить вклад\n";
        cout << "4. Показать все вклады\n";
        cout << "5. Поиск\n";
        cout << "6. Фильтровать\n";
        cout << "7. Сортировать\n";
        cout << "8. Показать новые вклады за месяц\n";
        cout << "9. Удалить пользователя\n";
        cout << "10. Зарегистрировать нового пользователя\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 10) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            addDeposit();
        } else if (choice == 2) {
            editDeposit();
        } else if (choice == 3) {
            deleteDeposit();
        } else if (choice == 4) {
            showDeposits();
        } else if (choice == 5) {
            subAdminSearchMenu();
        } else if (choice == 6) {
            subAdminFilterMenu();
        } else if (choice == 7) {
            subAdminSortMenu();
        } else if (choice == 8) {
            showNewThisMonth();
        } else if (choice == 9) {
            deleteUser();
        } else if (choice == 10) {
            registerUser();
        }
    }
}

// Подменю поиска для администратора
void BankSystem::subAdminSearchMenu() {
    while (true) {
        cout << "\nПоиск:\n";
        cout << "1. Поиск по фамилии\n";
        cout << "2. Поиск по ID\n";
        cout << "3. Поиск по сумме\n";
        cout << "4. Поиск по дате\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 4) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            searchBySurname();
        } else if (choice == 2) {
            searchByID();
        } else if (choice == 3) {
            searchByAmount();
        } else if (choice == 4) {
            searchByDate();
        }
    }
}

// Подменю фильтрации для администратора
void BankSystem::subAdminFilterMenu() {
    while (true) {
        cout << "\nФильтрация:\n";
        cout << "1. Фильтровать по сумме\n"
                "2. Фильтровать по дате\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            filterByAmount();
        }
        else if (choice == 2) {
            filterByDate();
        }
    }
}

// Подменю сортировки для администратора
void BankSystem::subAdminSortMenu() {
    while (true) {
        cout << "\nСортировка:\n";
        cout << "1. Сортировать по фамилии\n";
        cout << "2. Сортировать по ID\n";
        cout << "3. Сортировать по сумме\n";
        cout << "4. Сортировать по дате\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 4) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            sortBySurname();
        } else if (choice == 2) {
            sortByID();
        } else if (choice == 3) {
            sortByAmount();
        } else if (choice == 4) {
            sortByDate();
        }
    }
}

// Меню пользователя
void BankSystem::userMenu() {
    while (true) {
        cout << "\nМеню пользователя:\n";
        cout << "1. Добавить вклад\n";
        cout << "2. Редактировать вклад\n";
        cout << "3. Удалить вклад\n";
        cout << "4. Показать мои вклады\n";
        cout << "5. Поиск\n";
        cout << "6. Фильтровать\n";
        cout << "7. Сортировать\n";
        cout << "8. Показать новые вклады за последний месяц\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 8) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            addDeposit();
        } else if (choice == 2) {
            editDeposit();
        } else if (choice == 3) {
            deleteDeposit();
        } else if (choice == 4) {
            showDeposits();
        } else if (choice == 5) {
            subUserSearchMenu();
        } else if (choice == 6) {
            subUserFilterMenu();
        } else if (choice == 7) {
            subUserSortMenu();
        } else if (choice == 8) {
            showNewThisMonth();
        }
    }
}

// Подменю поиска для пользователя
void BankSystem::subUserSearchMenu() {
    while (true) {
        cout << "\nПоиск:\n";
        cout << "1. Поиск по ID\n";
        cout << "2. Поиск по сумме\n";
        cout << "3. Поиск по дате\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 3) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            searchByID();
        } else if (choice == 2) {
            searchByAmount();
        } else if (choice == 3) {
            searchByDate();
        }
    }
}

// Подменю фильтрации для пользователя
void BankSystem::subUserFilterMenu() {
    while (true) {
        cout << "\nФильтрация:\n";
        cout << "1. Фильтровать по сумме\n"
                "2. Фильтровать по дате\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            filterByAmount();
        }
        else if (choice == 2) {
            filterByDate();
        }
    }
}

// Подменю сортировки для пользователя
void BankSystem::subUserSortMenu() {
    while (true) {
        cout << "\nСортировка:\n";
        cout << "1. Сортировать по ID\n";
        cout << "2. Сортировать по сумме\n";
        cout << "3. Сортировать по дате\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 3) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            sortByID();
        } else if (choice == 2) {
            sortByAmount();
        } else if (choice == 3) {
            sortByDate();
        }
    }
}

// Запуск программы
void BankSystem::start() {
    while (true) {

        cout << "\nБанковская система\n";
        cout << "1. Войти\n";
        cout << "2. Зарегистрироваться\n";
        cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            std::cout << " /_/\\ /_/\\  \n"
                 " /  ^.^  \\   bye~ *paw*\n"
                 "/   >w<   \\ \n"
                 "/ /  ___  \\ \\ \n"
                 "| | /   \\ | | \n"
                 "| |/     \\| | \n"
                 " \\_\\_______/_/ \n"
                 "      /\\ \n"
                 "     /  \\ \n"
                 "    /    \\ \n";
            break;
        } else if (choice == 1) {
            if (logIn()) {
                if (currentUser->isAdmin()) {
                    adminMenu();
                } else {
                    userMenu();
                }
            }
        } else if (choice == 2) {
            registerUser();
        }
    }
}