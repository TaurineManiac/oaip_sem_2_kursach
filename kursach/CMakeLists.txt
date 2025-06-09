cmake_minimum_required(VERSION 3.10)
project(Kursach)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Kursach
        main.cpp
        functions.cpp
        user_management.cpp
        deposit_management.cpp
        search_filter.cpp
        sorting.cpp
        menu.cpp
)