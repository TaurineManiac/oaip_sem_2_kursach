#ifndef KURSACH_HEADER_H
#define KURSACH_HEADER_H

#include <iostream>
#include <string>

using namespace std;

class Deposit {
private:
    string surname;
    string name;
    float amount;
    int day;
    int month;
    int year;
    int depositID;

public:
    Deposit(string s = "", string n = "", float a = 0, int d = 1, int m = 1, int y = 2025, int id = 0);
    string getSurname() const;
    string getName() const;
    float getAmount() const;
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

    void loadDeposits();
    void saveDeposits();
    bool logIn();
    void registerUser();
    bool isUsernameTaken(string login);
    void showDeposits();
    void addDeposit();
    void editDeposit();
    void deleteDeposit();
    void searchBySurname();
    void searchByID();
    void searchByAmount();
    void searchByDate();
    void filterByAmount();
    void sortBySurname();
    void sortByID();
    void sortByAmount();
    void sortByDate();
    void showNewThisMonth();
    void deleteUser();
    void adminMenu();
    void userMenu();

public:
    BankSystem();
    ~BankSystem();
    void start();
};

#endif // KURSACH_HEADER_H