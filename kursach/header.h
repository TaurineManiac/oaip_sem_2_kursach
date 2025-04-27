#ifndef KURSACH_HEADER_H
#define KURSACH_HEADER_H

#include <iostream>
#include <string>
#include "inputCheck.h"
#include "generate.h"

using namespace std;

// Объявления вспомогательных функций
extern bool isLeapYear(int year);
extern int getDaysInMonth(int month, int year);

class Deposit {
private:
    string surname;
    string name;
    double amount;
    int day;
    int month;
    int year;
    int depositID;

public:
    Deposit(string s = "", string n = "", double a = 0, int d = 1, int m = 1, int y = 2025, int id = 0);
    string getSurname() const;
    string getName() const;
    double getAmount() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getDepositId() const;
};

class User {
protected:
    string username;
    string password;
    string surname;
    string name;

public:
    User(string u = "", string p = "", string s = "", string n = "");
    virtual ~User();
    string getUsername();
    string getPassword();
    string getSurname() const;
    string getName() const;
    virtual bool isAdmin() const = 0;
};

class Admin : public User {
public:
    Admin(string u = "", string p = "", string s = "", string n = "");
    virtual bool isAdmin() const override;
};

class RegularUser : public User {
public:
    RegularUser(string u = "", string p = "", string s = "", string n = "");
    virtual bool isAdmin() const override;
};

class BankSystem {
private:
    User** users;
    int countUsers;
    int userCapacity;
    User* currentUser;
    Deposit* deposits;
    int depositsCount;
    int depositsCapacity;

public:
    BankSystem();
    ~BankSystem();

    // Методы управления пользователями
    bool logIn();
    void registerUser();
    bool isUsernameTaken(string login);
    void deleteUser();
    void loadUsers();
    void saveUsers();

    // Методы управления вкладами
    void loadDeposits();
    void saveDeposits();
    void showDeposits();
    void addDeposit();
    void editDeposit();
    void deleteDeposit();

    // Методы поиска и фильтрации
    void searchBySurname();
    void searchByID();
    void searchByAmount();
    void searchByDate();
    void filterByAmount();
    void filterByDate();
    void showNewThisMonth();

    // Методы сортировки
    void sortBySurname();
    void sortByID();
    void sortByAmount();
    void sortByDate();

    // Методы меню
    //admin
    void adminMenu();
    void subAdminSearchMenu();
    void subAdminSortMenu();
    void subAdminFilterMenu();
    //user
    void userMenu();
    void subUserSearchMenu();
    void subUserSortMenu();
    void subUserFilterMenu();
    void start();

    // Новый метод для проверки депозита
    bool isOtherUserDeposit(int depositIndex) const;
};

// Объявления функций расширения массивов
User** expandUsers(User** oldUsers, int& capacity);
Deposit* expandDeposits(Deposit* oldDeposits, int& capacity);

#endif // KURSACH_HEADER_H