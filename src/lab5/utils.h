#ifndef OAIP_LABS2_UTILS_H
#define OAIP_LABS2_UTILS_H

#include "cache.h"

typedef struct {
    int len;
    char **str;
} string;

string *split(char *input, char *delimiter);

int is_ip(const char *str);

char *file_read(char path[]);

void fill_cache(LRUCache *cache);

void get_in_file(char *key, LRUCache *cache);

#endif //OAIP_LABS2_UTILS_H
