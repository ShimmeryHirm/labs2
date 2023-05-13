cmake_minimum_required(VERSION 3.23)
project(oaip_labs2 C)

set(CMAKE_C_STANDARD 99)

add_executable(test src/test.c)

add_executable(lab1 src/lab1/main.c src/lab1/utils.h src/lab1/utils.c src/lab1/sort.h src/lab1/sort.c)

add_executable(compress src/lab2/main.compressor.c src/lab2/utils.h src/lab2/utils.c src/lab2/linked_lists.h src/lab2/linked_lists.c
        src/lab2/compress.h src/lab2/compress.c)

add_executable(decompress src/lab2/main.decompressor.c src/lab2/utils.h src/lab2/utils.c src/lab2/linked_lists.h src/lab2/linked_lists.c
        src/lab2/decompress.h src/lab2/decompress.c)

add_executable(lab3 src/lab3/main.c src/lab3/bitmap.c src/lab3/bitmap.h src/lab3/filters.c src/lab3/filters.h)

add_executable(lab4 src/lab4/main.c src/lab4/tree.c src/lab4/tree.h)

add_executable(lab5 src/lab5/main.c src/lab5/cache.c src/lab5/cache.h src/lab5/tasks.c src/lab5/tasks.h src/lab5/utils.c src/lab5/utils.h src/lab5/config.h)