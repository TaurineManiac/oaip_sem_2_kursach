#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <iomanip>
#include "header.h"

// Загрузка вкладов из файла Deposits.txt
void BankSystem::loadDeposits() {
    std::ifstream file("Deposits.txt");
    if (!file.is_open()) {
        std::cout << "Файл Deposits.txt не найден. Будет создан новый файл при сохранении.\n";
        return;
    }
    depositsCount = 0;
    delete[] deposits;
    depositsCapacity = 5;
    deposits = new Deposit[depositsCapacity];
    if (!deposits) {
        file.close();
        throw std::runtime_error("Ошибка выделения памяти для вкладов в loadDeposits");
    }

    std::string s, n;
    double a; // Изменено с float на double
    int d, m, y, id;
    // Получение текущей даты
    std::string currentDate = generate::generateCurrentDataTime(); // Формат: YYYY-MM-DD HH:MM:SS
    int currentYear;
    try {
        currentYear = std::stoi(currentDate.substr(0, 4));
    } catch (...) {
        std::cout << "Ошибка получения текущей даты. Используется 2025 год.\n";
        currentYear = 2025;
    }

    while (file >> s >> n >> a >> d >> m >> y >> id) {
        // Валидация даты
        if (y > currentYear || y < 2000 || m < 1 || m > 12 || d < 1 || d > getDaysInMonth(m, y)) {
            std::cout << "Пропущен некорректный вклад: " << s << " " << n << ", дата: " << d << "." << m << "." << y << "\n";
            continue;
        }
        if (y == currentYear) {
            int currentMonth = std::stoi(currentDate.substr(5, 2));
            if (m > currentMonth) {
                std::cout << "Пропущен некorректный вклад: " << s << " " << n << ", дата: " << d << "." << m << "." << y << "\n";
                continue;
            }
            if (m == currentMonth) {
                int currentDay = std::stoi(currentDate.substr(8, 2));
                if (d > currentDay) {
                    std::cout << "Пропущен некорректный вклад: " << s << " " << n << ", дата: " << d << "." << m << "." << y << "\n";
                    continue;
                }
            }
        }
        if (depositsCount == depositsCapacity) {
            deposits = expandDeposits(deposits, depositsCapacity);
        }
        deposits[depositsCount] = Deposit(s, n, a, d, m, y, id);
        depositsCount++;
    }
    file.close();
}

// Сохранение вкладов в файл Deposits.txt
void BankSystem::saveDeposits() {
    std::ofstream file("Deposits.txt");
    if (!file.is_open()) {
        return;
    }
    file << std::fixed << std::setprecision(6); // Устанавливаем точность для double
    for (int i = 0; i < depositsCount; i++) {
        file << deposits[i].getSurname() << " " << deposits[i].getName() << " "
             << deposits[i].getAmount() << " " << deposits[i].getDay() << " "
             << deposits[i].getMonth() << " " << deposits[i].getYear() << " "
             << deposits[i].getDepositId() << std::endl;
    }
    file.close();
}

// Отображение списка вкладов
void BankSystem::showDeposits() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }
    std::cout << "Список вкладов:\n";
    std::cout << std::fixed << std::setprecision(6); // Устанавливаем точность для double
    for (int i = 0; i < depositsCount; i++) {
        if (!currentUser->isAdmin() && (deposits[i].getSurname() != currentUser->getSurname() ||
                                        deposits[i].getName() != currentUser->getName())) {
            continue;
        }
        std::cout << "ID: " << deposits[i].getDepositId() << " | "
                  << deposits[i].getSurname() << " " << deposits[i].getName() << ", "
                  << deposits[i].getAmount() << " руб., дата: " << deposits[i].getDay() << "."
                  << deposits[i].getMonth() << "." << deposits[i].getYear() << std::endl;
    }
}

// Добавление нового вклада
void BankSystem::addDeposit() {
    if (!currentUser) {
        std::cout << "Сначала войдите в систему!\n";
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

    std::string s, n;
    if (currentUser->isAdmin()) {
        std::cout << "Введите фамилию: ";
        s = mylib::checkTryToInputString(true); // Разрешаем кириллицу
        std::cout << "Введите имя: ";
        n = mylib::checkTryToInputString(true); // Разрешаем кириллицу
    } else {
        s = currentUser->getSurname();
        n = currentUser->getName();
    }

    double a; // Изменено с float на double
    std::cout << "Введите сумму вклада: ";
    while (true) {
        a = mylib::checkTryToInputDouble();
        if (a <= 0) {
            std::cout << "Сумма должна быть больше 0. Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    int y;
    std::cout << "Введите год (2000-" << currentYear << "): ";
    while (true) {
        y = mylib::checkTryToInputInt();
        if (y < 2000 || y > currentYear) {
            std::cout << "Год должен быть от 2000 до " << currentYear << ". Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    int m;
    std::cout << "Введите месяц (1-12): ";
    while (true) {
        m = mylib::checkTryToInputInt();
        if (m < 1 || m > 12) {
            std::cout << "Месяц должен быть от 1 до 12. Попробуйте снова." << std::endl;
            continue;
        }
        // Ограничение на месяц только для текущего года
        if (y == currentYear && m > currentMonth) {
            std::cout << "Для " << currentYear << " года месяц не может быть позже текущего (" << currentMonth << "). Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    int d;
    std::cout << "Введите день: ";
    while (true) {
        d = mylib::checkTryToInputInt();
        int maxDays = getDaysInMonth(m, y);
        // Ограничение на день только для текущего года и текущего месяца
        if (y == currentYear && m == currentMonth) {
            maxDays = std::min(maxDays, currentDay);
        }
        if (d < 1 || d > maxDays) {
            std::cout << "В " << m << "-м месяце " << y << " года " << maxDays << " дней. Введите день от 1 до " << maxDays << ". Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    int id;
    bool idUnique = false;
    std::string idStr;
    while (!idUnique) {
        idStr = generate::generateStringIndex();
        try {
            id = std::stoi(idStr);
            idUnique = true;
            for (int i = 0; i < depositsCount; i++) {
                if (deposits[i].getDepositId() == id) {
                    idUnique = false;
                    break;
                }
            }
            if (!idUnique) {
                std::cout << "ID " << id << " уже занят, генерируем новый..." << std::endl;
            }
        } catch (...) {
            std::cout << "Ошибка генерации ID, пробуем снова..." << std::endl;
        }
    }

    if (depositsCount == depositsCapacity) {
        deposits = expandDeposits(deposits, depositsCapacity);
    }

    deposits[depositsCount] = Deposit(s, n, a, d, m, y, id);
    depositsCount++;
    saveDeposits();
    std::cout << "Вклад добавлен с ID " << id << "!\n";
}

// Редактирование вклада
void BankSystem::editDeposit() {
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

    showDeposits();
    std::cout << "Введите ID вклада для редактирования: ";
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
            std::cout << "Вы можете редактировать только свои вклады!\n";
        } else {
            std::cout << "Вклад с таким ID не найден.\n";
        }
        return;
    }

    double newAmount; // Изменено с float на double
    int newDay, newMonth, newYear;
    std::string newSurname = deposits[index].getSurname();
    std::string newName = deposits[index].getName();
    std::cout << "Редактирование вклада ID " << id << std::endl;

    std::cout << "Введите новую сумму: ";
    while (true) {
        newAmount = mylib::checkTryToInputDouble();
        if (newAmount <= 0) {
            std::cout << "Сумма должна быть больше 0. Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    std::cout << "Введите новый год (2000-" << currentYear << "): ";
    while (true) {
        newYear = mylib::checkTryToInputInt();
        if (newYear < 2000 || newYear > currentYear) {
            std::cout << "Год должен быть от 2000 до " << currentYear << ". Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    std::cout << "Введите новый месяц (1-12): ";
    while (true) {
        newMonth = mylib::checkTryToInputInt();
        if (newMonth < 1 || newMonth > 12) {
            std::cout << "Месяц должен быть от 1 до 12. Попробуйте снова." << std::endl;
            continue;
        }
        // Ограничение на месяц только для текущего года
        if (newYear == currentYear && newMonth > currentMonth) {
            std::cout << "Для " << currentYear << " года месяц не может быть позже текущего (" << currentMonth << "). Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    std::cout << "Введите новый день: ";
    while (true) {
        newDay = mylib::checkTryToInputInt();
        int maxDays = getDaysInMonth(newMonth, newYear);
        // Ограничение на день только для текущего года и текущего месяца
        if (newYear == currentYear && newMonth == currentMonth) {
            maxDays = std::min(maxDays, currentDay);
        }
        if (newDay < 1 || newDay > maxDays) {
            std::cout << "В " << newMonth << "-м месяце " << newYear << " года " << maxDays << " дней. Введите день от 1 до " << maxDays << ". Попробуйте снова." << std::endl;
            continue;
        }
        break;
    }

    deposits[index] = Deposit(newSurname, newName, newAmount, newDay, newMonth, newYear, id);
    saveDeposits();
    std::cout << "Вклад отредактирован!\n";
}

// Удаление вклада
void BankSystem::deleteDeposit() {
    if (depositsCount == 0) {
        std::cout << "Вкладов нет.\n";
        return;
    }

    showDeposits();
    std::cout << "Введите ID вклада для удаления: ";
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
            std::cout << "Вы можете удалять только свои вклады!\n";
        } else {
            std::cout << "Вклад с таким ID не найден.\n";
        }
        return;
    }

    for (int i = index; i < depositsCount - 1; i++) {
        deposits[i] = deposits[i + 1];
    }
    depositsCount--;

    saveDeposits();
    std::cout << "Вклад удалён!\n";
}