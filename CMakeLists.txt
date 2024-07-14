cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

project(lbme LANGUAGES C CXX)

find_package(Curses REQUIRED)
set(CURSES_USE_NCURSES TRUE)
set(GIT_VERSION "$(shell git describe --abbrev=4 --dirty --always --tags)")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-DVERSION=\"$(GIT_VERSION)\"")

include_directories(cmake/)
add_subdirectory(src/)
