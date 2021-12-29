cmake_minimum_required(VERSION 3.20)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp book.h token_scanner.h unrolled_linked_list.h log.h book.cpp log.cpp token_scanner.cpp accounts.h accounts.cpp)
