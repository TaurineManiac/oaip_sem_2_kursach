#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>
#include "header.h" // Оставляем только этот заголовок

using namespace std;

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
    } else {
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
    } else {
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
    } else {
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