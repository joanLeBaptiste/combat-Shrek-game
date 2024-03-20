cmake_minimum_required(VERSION 3.27)
project(Shrek_V0_6 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Shrek_V0_6
        file.c
        file.h
        main.c
        menu.c)
target_link_libraries(Shrek_V0_6 -lmingw32 -lalleg44)

