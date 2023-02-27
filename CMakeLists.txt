cmake_minimum_required(VERSION 3.23)
project(oaip_labs2 C)

set(CMAKE_C_STANDARD 99)

add_executable(test src/test.c)

add_executable(lab1 src/lab1/main.c src/lab1/utils.h src/lab1/utils.c src/lab1/sort.h src/lab1/sort.c)

add_executable(compress src/lab2/main.compressor.c src/lab2/utils.h src/lab2/utils.c src/lab2/linked_lists.h src/lab2/linked_lists.c
        src/lab2/compress.h src/lab2/compress.c)

add_executable(decompress src/lab2/main.decompressor.c src/lab2/utils.h src/lab2/utils.c src/lab2/linked_lists.h src/lab2/linked_lists.c
        src/lab2/decompress.h src/lab2/decompress.c)