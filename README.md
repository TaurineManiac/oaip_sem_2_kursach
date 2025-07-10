# Coursework I from IEF, BSUIR
This C++ banking system implements secure financial operations
with hierarchical access control, demonstrating core programming 
concepts through file-based persistence and efficient
data processing. The console application maintains transaction
integrity between sessions while providing distinct interfaces
for administrators and regular clients. I use in this project 2
my own libraries: for [input validation](https://github.com/TaurineManiac/library_input_check) and [generation data](https://github.com/TaurineManiac/library_generate).
## Main features:

- **Dual-tier Authentication**  
  Role-based access for administrators and regular users with persistent session management

- **Data Persistence**  
  Robust file I/O operations maintain account/deposit records in text format

- **Transaction Lifecycle**  
  Full CRUD operations for deposit management with ownership validation

- **Multi-criteria Sorting**  
  Optimized algorithms for sorting by ID, amount, date, and client parameters

- **Intelligent Search**  
  Context-aware filtering by amount ranges, date periods, and custom identifiers

- **Account Governance**  
  Administrative tools for user account creation, modification, and deletion

- **Input Validation**  
  Type-safe data entry with comprehensive error handling

- **Memory Management**  
  Efficient dynamic allocation for user/deposit datasets with expansion capabilities

- **Many levels of User/Admin menu**  
  It shows the different levels of the function menu for different access levels.

⚠️ **Current limitations:**

1. **User data safety** - Modern programming doesn't use text files, much less without hashing.
2. **Optimization** - library [input_check](https://github.com/TaurineManiac/library_input_check) is too low in current world.
3. **Inconvenient input** - some methods are
supplemented in the program code rather than specified by the 
library, and not all methods are used by their intended purpose.
4. **Using bubble sort** - using this sorting is not rational.

## Main levels of menu:

### 1st level menu of admin/user:
| № | Menu option          | Description                      |
|---|----------------------|----------------------------------|
| 1 | "Войти"              | Entrance into an exiting account |
| 2 | "Зарегистрироваться" | Register new account             |
| 3 | "Выход"              | Stop program                     |

### 2d level of Admin menu:\
| №  | Menu option             | Description |
|----|-------------------------|-------------|
| 1  | "Добавить вклад"        | Create new banking deposit |
| 2  | "Редактировать вклад"   | Modify existing deposit |
| 3  | "Удалить вклад"         | Remove deposit record |
| 4  | "Показать все"          | Display all deposits |
| 5  | "Поиск"                 | Search deposits by criteria |
| 6  | "Фильтровать"           | Filter deposit list |
| 7  | "Сортировать"           | Sort deposits |
| 8  | "Новые за месяц"        | Show recent deposits |
| 9  | "Удалить пользователя"  | Remove user account |
| 10 | "Добавить пользователя" | Register new user |
| 11 | "Выход"                 | Exit admin mode |

### 2d level of User menu:

| №  | Опция меню | Description |
|----|------------|-------------|
| 1  | "Добавить вклад" | Create personal deposit |
| 2  | "Редактировать вклад" | Modify personal deposit |
| 3  | "Удалить вклад" | Delete personal deposit |
| 4  | "Мои вклады" | View personal deposits |
| 5  | "Поиск" | Search personal deposits |
| 6  | "Фильтровать" | Filter personal deposits |
| 7  | "Сортировать" | Sort personal deposits |
| 8  | "Новые за месяц" | Show recent personal deposits |
| 9  | "Выход" | Logout from system |

## List of Functions:
In order not to clutter it up,
I moved it [here](./ListOfFunctions.md).

## Link to the full report:
If you want to know more about my coursework, 
without reading code, you can read my 
[report](https://github.com/TaurineManiac/oaip_sem_2_kursach/blob/main/%D0%97%D0%B0%D0%BF%D0%B8%D1%81%D0%BA%D0%B0%20%D0%B7%D0%B0%D0%BF%D0%B8%D1%81%D0%BA%D0%B0%20%D0%B1%D0%B0%D0%BD%D0%BA%20YTTTTTTTTTTTTTTTTTTTTTTTTTTTTTN.docx)
, but only on RU.

## Lessons Learned:

🔧 **Development insights:**
- **Big project** - learned how to work in a big project.
- **Exceptions** - learned how to track logical/program exceptions.
- **Files** - improve working with files.
- **Libraries** - using own libraries in big project. 


