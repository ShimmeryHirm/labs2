cmake_minimum_required(VERSION 3.23)
project(oaip_labs2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab1 src/lab1/main.c src/lab1/utils.h src/lab1/utils.c src/lab1/sort.h src/lab1/sort.c)

add_executable(lab2 src/lab2/main.c src/lab2/utils.h src/lab2/utils.c src/lab2/linked_lists.h src/lab2/linked_lists.c
        src/lab2/compress.h src/lab2/compress.c src/lab2/decompress.h src/lab2/decompress.c)