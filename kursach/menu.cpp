#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "header.h"

// Меню администратора
void BankSystem::adminMenu() {
    while (true) {

        std::cout << "\nМеню администратора:\n";
        std::cout << "1. Добавить вклад\n";
        std::cout << "2. Редактировать вклад\n";
        std::cout << "3. Удалить вклад\n";
        std::cout << "4. Показать\n";
        std::cout << "5. Поиск\n";
        std::cout << "6. Фильтровать\n";
        std::cout << "7. Сортировать\n";
        std::cout << "8. Показать новые вклады за месяц\n";
        std::cout << "9. Удалить пользователя\n";
        std::cout << "10. Зарегистрировать нового пользователя\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 10) {
            std::cout << "Введите число в нужном диапазоне.\n";
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
            subAdminShowMenu();
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
        std::cout << "\nПоиск:\n";
        std::cout << "1. Поиск по фамилии\n";
        std::cout << "2. Поиск по ID\n";
        std::cout << "3. Поиск по сумме\n";
        std::cout << "4. Поиск по дате\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 4) {
            std::cout << "Введите число в нужном диапазоне.\n";
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
        std::cout << "\nФильтрация:\n";
        std::cout << "1. Фильтровать по сумме\n";
        std::cout << "2. Фильтровать по дате\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            std::cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            filterByAmount();
        } else if (choice == 2) {
            filterByDate();
        }
    }
}

// Подменю сортировки для администратора
void BankSystem::subAdminSortMenu() {
    while (true) {
        std::cout << "\nСортировка:\n";
        std::cout << "1. Сортировать по фамилии\n";
        std::cout << "2. Сортировать по ID\n";
        std::cout << "3. Сортировать по сумме\n";
        std::cout << "4. Сортировать по дате\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 4) {
            std::cout << "Введите число в нужном диапазоне.\n";
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

// Подменю показа для администратора
void BankSystem::subAdminShowMenu() {
    while (true) {
        std::cout << "\nПоказать:\n";
        std::cout << "1. Показать все депозиты\n";
        std::cout << "2. Показать всех пользователей\n";
        std::cout << "0. Выход\n"; // Добавлен пункт выхода
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            std::cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            showDeposits();
        } else if (choice == 2) {
            showUsers();
        }
    }
}

// Меню пользователя
void BankSystem::userMenu() {
    while (true) {

        std::cout << "\nМеню пользователя:\n";
        std::cout << "1. Добавить вклад\n";
        std::cout << "2. Редактировать вклад\n";
        std::cout << "3. Удалить вклад\n";
        std::cout << "4. Показать мои вклады\n";
        std::cout << "5. Поиск\n";
        std::cout << "6. Фильтровать\n";
        std::cout << "7. Сортировать\n";
        std::cout << "8. Показать новые вклады за последний месяц\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 8) {
            std::cout << "Введите число в нужном диапазоне.\n";
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
        std::cout << "\nПоиск:\n";
        std::cout << "1. Поиск по ID\n";
        std::cout << "2. Поиск по сумме\n";
        std::cout << "3. Поиск по дате\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 3) {
            std::cout << "Введите число в нужном диапазоне.\n";
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
        std::cout << "\nФильтрация:\n";
        std::cout << "1. Фильтровать по сумме\n";
        std::cout << "2. Фильтровать по дате\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            std::cout << "Введите число в нужном диапазоне.\n";
            choice = mylib::checkTryToInputInt();
        }
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            filterByAmount();
        } else if (choice == 2) {
            filterByDate();
        }
    }
}

// Подменю сортировки для пользователя
void BankSystem::subUserSortMenu() {
    while (true) {
        std::cout << "\nСортировка:\n";
        std::cout << "1. Сортировать по ID\n";
        std::cout << "2. Сортировать по сумме\n";
        std::cout << "3. Сортировать по дате\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 3) {
            std::cout << "Введите число в нужном диапазоне.\n";
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
        std::cout << "\nБанковская система\n";
        std::cout << "1. Войти\n";
        std::cout << "2. Зарегистрироваться\n";
        std::cout << "0. Выход\n";
        int choice = mylib::checkTryToInputInt();
        while (choice < 0 || choice > 2) {
            std::cout << "Введите число в нужном диапазоне.\n";
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