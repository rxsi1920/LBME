cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(lbme LANGUAGES C CXX)

find_package(Curses REQUIRED)
set(CURSES_USE_NCURSES TRUE)

include_directories(cmake/)
add_subdirectory(src/)
