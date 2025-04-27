#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <cmath>
#include <iomanip>
#include "header.h"

// Поиск вкладов по фамилии (только для администратора)
void BankSystem::searchBySurname() {
    if (!currentUser->isAdmin()) {
        std::cout << "Ошибка: поиск по фамилии доступен только администратору.\n";
        return;
    }

    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    std::cout << "Введите фамилию для поиска: ";
    std::string surname = mylib::checkTryToInputString(true); // Разрешаем кириллицу

    bool found = false;
    std::cout << "Найденные вклады:\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    for (int i = 0; i < depositsCount; i++) {
        std::string depositSurname = deposits[i].getSurname();
        if (depositSurname == surname) {
            std::cout << "ID: " << deposits[i].getDepositId() << " | "
                      << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                      << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                      << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Вклады не найдены.\n";
    }
}

// Поиск вкладов по ID
void BankSystem::searchByID() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    showDeposits();
    std::cout << "Введите ID вклада для поиска: ";
    int id = mylib::checkTryToInputInt();

    int index = -1;
    bool foundOtherUserDeposit = false;
    for (int i = 0; i < depositsCount; i++) {
        if (deposits[i].getDepositId() == id) {
            if (currentUser->isAdmin()) {
                index = i;
                break;
            } else {
                if (isOtherUserDeposit(i)) {
                    foundOtherUserDeposit = true;
                } else {
                    index = i;
                    break;
                }
            }
        }
    }

    if (index == -1) {
        if (foundOtherUserDeposit) {
            std::cout << "Вы можете просматривать только свои вклады!\n";
        } else {
            std::cout << "Вклад с таким ID не найден.\n";
        }
        return;
    }

    std::cout << "Найден вклад:\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    std::cout << "ID: " << deposits[index].getDepositId() << " | "
              << deposits[index].getSurname() << " " << deposits[index].getName() << ", "
              << deposits[index].getAmount() << " руб., дата: " << deposits[index].getDay() << "."
              << deposits[index].getMonth() << "." << deposits[index].getYear() << std::endl;
}

// Поиск вкладов по сумме
void BankSystem::searchByAmount() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    std::cout << "Введите сумму для поиска: ";
    double amount = mylib::checkTryToInputDouble();
    if (amount <= 0) {
        std::cout << "Сумма должна быть больше 0.\n";
        return;
    }

    bool found = false;
    std::cout << "Найденные вклады:\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        if (std::abs(deposits[i].getAmount() - amount) < 0.01) {
            std::cout << "ID: " << deposits[i].getDepositId() << " | "
                      << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                      << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                      << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Вклады не найдены.\n";
    }
}

// Поиск вкладов по дате
void BankSystem::searchByDate() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    // Получение текущей даты
    std::string currentDate = generate::generateCurrentDataTime(); // Формат: YYYY-MM-DD HH:MM:SS
    int currentYear, currentMonth, currentDay;
    try {
        currentYear = std::stoi(currentDate.substr(0, 4));
        currentMonth = std::stoi(currentDate.substr(5, 2));
        currentDay = std::stoi(currentDate.substr(8, 2));
    } catch (...) {
        std::cout << "Ошибка получения текущей даты.\n";
        return;
    }

    std::cout << "Введите год (2000-" << currentYear << "): ";
    int year = mylib::checkTryToInputInt();
    if (year < 2000 || year > currentYear) {
        std::cout << "Год должен быть от 2000 до " << currentYear << ".\n";
        return;
    }

    std::cout << "Введите месяц (1-12): ";
    int month = mylib::checkTryToInputInt();
    if (month < 1 || month > 12) {
        std::cout << "Месяц должен быть от 1 до 12.\n";
        return;
    }
    // Ограничение на месяц только для текущего года
    if (year == currentYear && month > currentMonth) {
        std::cout << "Для " << currentYear << " года месяц не может быть позже текущего (" << currentMonth << ").\n";
        return;
    }

    int maxDays = getDaysInMonth(month, year);
    // Ограничение на день только для текущего года и текущего месяца
    if (year == currentYear && month == currentMonth) {
        maxDays = std::min(maxDays, currentDay);
    }

    std::cout << "Введите день (1-" << maxDays << "): ";
    int day = mylib::checkTryToInputInt();
    if (day < 1 || day > maxDays) {
        std::cout << "В " << month << "-м месяце " << year << " года " << maxDays << " дней. Введите день от 1 до " << maxDays << ".\n";
        return;
    }

    bool found = false;
    std::cout << "Найденные вклады:\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        if (deposits[i].getDay() == day &&
            deposits[i].getMonth() == month &&
            deposits[i].getYear() == year) {
            std::cout << "ID: " << deposits[i].getDepositId() << " | "
                      << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                      << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                      << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Вклады не найдены.\n";
    }
}

// Фильтрация вкладов по сумме
void BankSystem::filterByAmount() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    std::cout << "Введите минимальную сумму: ";
    double minAmount = mylib::checkTryToInputDouble();
    if (minAmount <= 0) {
        std::cout << "Сумма должна быть больше 0.\n";
        return;
    }

    std::cout << "Введите максимальную сумму: ";
    double maxAmount = mylib::checkTryToInputDouble();
    if (maxAmount <= 0 || maxAmount < minAmount) {
        std::cout << "Максимальная сумма должна быть больше 0 и не меньше минимальной.\n";
        return;
    }

    bool found = false;
    std::cout << "Вклады в диапазоне от " << minAmount << " до " << maxAmount << " руб.:\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        double amount = deposits[i].getAmount();
        if (amount >= minAmount && amount <= maxAmount) {
            std::cout << "ID: " << deposits[i].getDepositId() << " | "
                      << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                      << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                      << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Вклады не найдены.\n";
    }
}

// Фильтрация вкладов по дате
void BankSystem::filterByDate() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    // Получение текущей даты
    std::string currentDate = generate::generateCurrentDataTime(); // Формат: YYYY-MM-DD HH:MM:SS
    int currentYear, currentMonth, currentDay;
    try {
        currentYear = std::stoi(currentDate.substr(0, 4));
        currentMonth = std::stoi(currentDate.substr(5, 2));
        currentDay = std::stoi(currentDate.substr(8, 2));
    } catch (...) {
        std::cout << "Ошибка получения текущей даты.\n";
        return;
    }

    // Ввод начальной даты
    std::cout << "Введите начальную дату для фильтрации:\n";
    std::cout << "Год (2000-" << currentYear << "): ";
    int startYear = mylib::checkTryToInputInt();
    if (startYear < 2000 || startYear > currentYear) {
        std::cout << "Год должен быть от 2000 до " << currentYear << ".\n";
        return;
    }

    std::cout << "Месяц (1-12): ";
    int startMonth = mylib::checkTryToInputInt();
    if (startMonth < 1 || startMonth > 12) {
        std::cout << "Месяц должен быть от 1 до 12.\n";
        return;
    }
    // Ограничение на месяц только для текущего года
    if (startYear == currentYear && startMonth > currentMonth) {
        std::cout << "Для " << currentYear << " года месяц не может быть позже текущего (" << currentMonth << ").\n";
        return;
    }

    int maxStartDays = getDaysInMonth(startMonth, startYear);
    // Ограничение на день только для текущего года и текущего месяца
    if (startYear == currentYear && startMonth == currentMonth) {
        maxStartDays = std::min(maxStartDays, currentDay);
    }

    std::cout << "День (1-" << maxStartDays << "): ";
    int startDay = mylib::checkTryToInputInt();
    if (startDay < 1 || startDay > maxStartDays) {
        std::cout << "В " << startMonth << "-м месяце " << startYear << " года " << maxStartDays << " дней. Введите день от 1 до " << maxStartDays << ".\n";
        return;
    }

    // Ввод конечной даты
    std::cout << "Введите конечную дату для фильтрации:\n";
    std::cout << "Год (2000-" << currentYear << "): ";
    int endYear = mylib::checkTryToInputInt();
    if (endYear < 2000 || endYear > currentYear) {
        std::cout << "Год должен быть от 2000 до " << currentYear << ".\n";
        return;
    }

    std::cout << "Месяц (1-12): ";
    int endMonth = mylib::checkTryToInputInt();
    if (endMonth < 1 || endMonth > 12) {
        std::cout << "Месяц должен быть от 1 до 12.\n";
        return;
    }
    // Ограничение на месяц только для текущего года
    if (endYear == currentYear && endMonth > currentMonth) {
        std::cout << "Для " << currentYear << " года месяц не может быть позже текущего (" << currentMonth << ").\n";
        return;
    }

    int maxEndDays = getDaysInMonth(endMonth, endYear);
    // Ограничение на день только для текущего года и текущего месяца
    if (endYear == currentYear && endMonth == currentMonth) {
        maxEndDays = std::min(maxEndDays, currentDay);
    }

    std::cout << "День (1-" << maxEndDays << "): ";
    int endDay = mylib::checkTryToInputInt();
    if (endDay < 1 || endDay > maxEndDays) {
        std::cout << "В " << endMonth << "-м месяце " << endYear << " года " << maxEndDays << " дней. Введите день от 1 до " << maxEndDays << ".\n";
        return;
    }

    // Проверка, что начальная дата не позже конечной
    if (startYear > endYear ||
        (startYear == endYear && startMonth > endMonth) ||
        (startYear == endYear && startMonth == endMonth && startDay > endDay)) {
        std::cout << "Начальная дата не может быть позже конечной.\n";
        return;
    }

    // Фильтрация вкладов
    bool found = false;
    std::cout << "Вклады в диапазоне дат от " << startDay << "." << startMonth << "." << startYear
              << " до " << endDay << "." << endMonth << "." << endYear << ":\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }

        int depositYear = deposits[i].getYear();
        int depositMonth = deposits[i].getMonth();
        int depositDay = deposits[i].getDay();

        // Проверка, попадает ли дата вклада в диапазон
        bool afterStart = (depositYear > startYear) ||
                          (depositYear == startYear && depositMonth > startMonth) ||
                          (depositYear == startYear && depositMonth == startMonth && depositDay >= startDay);
        bool beforeEnd = (depositYear < endYear) ||
                         (depositYear == endYear && depositMonth < endMonth) ||
                         (depositYear == endYear && depositMonth == endMonth && depositDay <= endDay);

        if (afterStart && beforeEnd) {
            std::cout << "ID: " << deposits[i].getDepositId() << " | "
                      << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                      << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                      << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Вклады не найдены.\n";
    }
}

// Показ новых вкладов за текущий месяц
void BankSystem::showNewThisMonth() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    std::string currentDate = generate::generateCurrentDataTime(); // Формат: YYYY-MM-DD HH:MM:SS
    int currentYear, currentMonth;
    try {
        currentYear = std::stoi(currentDate.substr(0, 4));
        currentMonth = std::stoi(currentDate.substr(5, 2));
    } catch (...) {
        std::cout << "Ошибка получения текущей даты.\n";
        return;
    }

    bool found = false;
    std::cout << "Вклады за " << currentMonth << "/" << currentYear << ":\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() &&
            (deposits[i].getSurname() != currentUser->getSurname() ||
             deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        if (deposits[i].getMonth() == currentMonth && deposits[i].getYear() == currentYear) {
            std::cout << "ID: " << deposits[i].getDepositId() << " | "
                      << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                      << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                      << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Вклады за этот месяц не найдены.\n";
    }
}