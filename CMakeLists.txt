cmake_minimum_required(VERSION 3.17)
project(Bank_System)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bank_System
        main.cpp
        src/Account.h
        src/Account.cpp
        src/Pay.h
        src/Pay.cpp
        )