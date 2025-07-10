## List of functions:

| Function | Description | Regular User | Admin |
|----------|-------------|--------------|-------|
| **`expandUsers(User* oldUsers, int& capacity)`** | Expands user array by 2 slots | No | Yes |
| **`expandDeposits(Deposit* oldDeposits, int& capacity)`** | Expands deposits array by 5 slots | No | Yes |
| **`BankSystem::loadDeposits()`** | Loads deposits from Deposits.txt | No | No |
| **`BankSystem::saveDeposits()`** | Saves deposits to Deposits.txt | No | No |
| **`BankSystem::showDeposits()`** | Displays all/specific deposits | Yes | Yes |
| **`BankSystem::addDeposit()`** | Adds new deposit | Yes | Yes |
| **`BankSystem::editDeposit()`** | Edits existing deposit | Yes | Yes |
| **`BankSystem::deleteDeposit()`** | Deletes deposit by ID | Yes | Yes |
| **`isLeapYear(int year)`** | Checks for leap year | Yes | Yes |
| **`getDaysInMonth(int month, int year)`** | Gets days in month | Yes | Yes |
| **`User::getPassword()`** | Returns user password | No | No |
| **`User::getUsername()`** | Returns username | No | No |
| **`User::getSurname() const`** | Returns user surname | Yes | Yes |
| **`User::getName() const`** | Returns user name | Yes | Yes |
| **`User::User(string u, string p, string s, string n)`** | User constructor | No | No |
| **`User::~User()`** | User destructor | No | No |
| **`Admin::isAdmin() const`** | Admin status check | No | Yes |
| **`Admin::Admin(string u, string p, string s, string n)`** | Admin constructor | No | No |
| **`RegularUser::isAdmin() const`** | Admin status check | No | No |
| **`RegularUser::RegularUser(string u, string p, string s, string n)`** | RegularUser constructor | No | No |
| **`Deposit::Deposit(string s, string n, double a, int d, int m, int y, int id)`** | Deposit constructor | No | No |
| **`Deposit::getSurname() const`** | Returns owner surname | Yes | Yes |
| **`Deposit::getName() const`** | Returns owner name | Yes | Yes |
| **`Deposit::getAmount() const`** | Returns deposit amount | Yes | Yes |
| **`Deposit::getDay() const`** | Returns creation day | Yes | Yes |
| **`Deposit::getMonth() const`** | Returns creation month | Yes | Yes |
| **`Deposit::getYear() const`** | Returns creation year | Yes | Yes |
| **`Deposit::getDepositId() const`** | Returns deposit ID | Yes | Yes |
| **`BankSystem::BankSystem()`** | System constructor | No | No |
| **`BankSystem::~BankSystem()`** | System destructor | No | No |
| **`BankSystem::isOtherUserDeposit(int depositIndex) const`** | Checks deposit ownership | No | No |
| **`BankSystem::adminMenu()`** | Admin control panel | No | Yes |
| **`BankSystem::subAdminSearchMenu()`** | Admin search options | No | Yes |
| **`BankSystem::subAdminFilterMenu()`** | Admin filter options | No | Yes |
| **`BankSystem::subAdminSortMenu()`** | Admin sort options | No | Yes |
| **`BankSystem::subAdminShowMenu()`** | Admin display options | No | Yes |
| **`BankSystem::userMenu()`** | User control panel | Yes | No |
| **`BankSystem::subUserSearchMenu()`** | User search options | Yes | No |
| **`BankSystem::subUserFilterMenu()`** | User filter options | Yes | No |
| **`BankSystem::subUserSortMenu()`** | User sort options | Yes | No |
| **`BankSystem::start()`** | Program entry point | Yes | Yes |
| **`BankSystem::searchBySurname()`** | Search deposits by surname | No | Yes |
| **`BankSystem::searchByID()`** | Search deposit by ID | Yes | Yes |
| **`BankSystem::searchByAmount()`** | Search deposits by amount | Yes | Yes |
| **`BankSystem::searchByDate()`** | Search deposits by date | Yes | Yes |
| **`BankSystem::filterByAmount()`** | Filter deposits by amount | Yes | Yes |
| **`BankSystem::filterByDate()`** | Filter deposits by date | Yes | Yes |
| **`BankSystem::showNewThisMonth()`** | Show new monthly deposits | Yes | Yes |
| **`BankSystem::sortBySurname()`** | Sort deposits by surname | No | Yes |
| **`BankSystem::sortByID()`** | Sort deposits by ID | Yes | Yes |
| **`BankSystem::sortByAmount()`** | Sort deposits by amount | Yes | Yes |
| **`BankSystem::sortByDate()`** | Sort deposits by date | Yes | Yes |
| **`BankSystem::loadUsers()`** | Load users from Users.txt | No | No |
| **`BankSystem::saveUsers()`** | Save users to Users.txt | No | No |
| **`BankSystem::logIn()`** | User authentication | Yes | Yes |
| **`BankSystem::registerUser()`** | New user registration | Yes | Yes |
| **`BankSystem::isUsernameTaken(string login)`** | Check username availability | No | No |
| **`BankSystem::deleteUser()`** | Delete user account | No | Yes |
| **`BankSystem::showUsers()`** | Display all users | No | Yes |


[return back](./README.md)
