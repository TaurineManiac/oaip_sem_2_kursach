#include "header.h"
#include <stdexcept>

User** expandUsers(User** oldUsers, int& capacity) {
    int newCapacity = capacity + 2;
    User** newUsers = new User*[newCapacity];
    if (!newUsers) {
        throw std::runtime_error("Ошибка выделения памяти для пользователей");
    }
    for (int i = 0; i < capacity; i++) {
        newUsers[i] = oldUsers[i];
    }
    for (int i = capacity; i < newCapacity; i++) {
        newUsers[i] = nullptr;
    }
    delete[] oldUsers;
    capacity = newCapacity;
    return newUsers;
}

Deposit* expandDeposits(Deposit* oldDeposits, int& capacity) {
    int newCapacity = capacity + 5;
    Deposit* newDeposits = new Deposit[newCapacity];
    if (!newDeposits) {
        throw std::runtime_error("Ошибка выделения памяти для депозитов");
    }
    for (int i = 0; i < capacity; i++) {
        newDeposits[i] = oldDeposits[i];
    }
    delete[] oldDeposits;
    capacity = newCapacity;
    return newDeposits;
}