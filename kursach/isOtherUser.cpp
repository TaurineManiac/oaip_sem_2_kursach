#include "header.h"

bool BankSystem::isOtherUserDeposit(int depositIndex) const {
    return !currentUser->isAdmin() &&
           (deposits[depositIndex].getSurname() != currentUser->getSurname() ||
            deposits[depositIndex].getName() != currentUser->getName());
}