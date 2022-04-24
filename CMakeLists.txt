cmake_minimum_required(VERSION 3.17)
project(Battleship C)

set(SRCS
        main.c
        grid.c
        menu.c
        missiles.c
        save.c
        verifications.c)

set(HEADERS
        structures.h
        grid.h
        menu.h
        missiles.h
        save.h
        verifications.h)

add_executable(Battleship ${SRCS} ${HEADERS})