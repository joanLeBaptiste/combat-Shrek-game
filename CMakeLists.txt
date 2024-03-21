cmake_minimum_required(VERSION 3.27)
project(project_dofus__theme_Shrek C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(project_dofus__theme_Shrek
        file.c
        file.h
        main.c
        menu.c
        movement.c)
target_link_libraries(project_dofus__theme_Shrek -lmingw32 -lalleg44)

