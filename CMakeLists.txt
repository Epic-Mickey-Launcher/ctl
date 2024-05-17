cmake_minimum_required(VERSION 3.27)
project(emlctl C)

set(CMAKE_C_STANDARD 11)

add_executable(emlctl src/main.c src/query.c src/query.h src/help.c src/help.h)
