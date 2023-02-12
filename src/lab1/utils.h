//
// Created by shh on 12.02.2023.
//

#ifndef OAIP_LABS2_UTILS_H
#define OAIP_LABS2_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {
    unique, inscribed, autographed, corrupted
} item_quality;



typedef struct {
    char *name;
    int quantity;
    double price;
    item_quality quality;
} item;

typedef struct {
    int len;
    char **str;
} string;

string *split(char *input, char *delimiter);

char *file_read(char path[]);

int startswith(const char *pre, const char *str);

#endif //OAIP_LABS2_UTILS_H
