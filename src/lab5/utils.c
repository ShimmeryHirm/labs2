#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "cache.h"
#include "config.h"


string *split(char *input, char *delimiter) {

    char *input_copy = strdup(input);
    string *str = malloc(sizeof(string));
    str->str = NULL;
    str->len = 0;

    char *token = strtok(input_copy, delimiter);

    while (token != NULL) {
        str->str = realloc(str->str, (str->len + 1) * sizeof(char *));
        str->str[str->len++] = token;
        token = strtok(NULL, delimiter);
    }

    return str;
}


int is_ip(const char *str) {

    int num, dots = 0;
    int res = 1;

    while (*str) {
        if (*str >= '0' && *str <= '9') {
            num = 0;

            while (*str >= '0' && *str <= '9') {
                num = num * 10 + (*str - '0');
                str++;
            }

            if (num < 0 || num > 255) {
                res = 0;
                break;
            }

            if (*str != '\0' && *str != '.') {
                res = 0;
                break;
            }

            if (*str == '.')
                dots++;
        } else {
            res = 0;
            break;
        }
        str++;
    }

    if (dots != 3 || strlen(str) != 0)
        res = 0;

    return res;
}


char *file_read(char path[]) {

    long length;

    FILE *f = fopen(path, "r");
    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = calloc(length, 1);

    fread(buffer, 1, length, f);
    fclose(f);

    return buffer;
}

void fill_cache(LRUCache *cache) {

    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(RECORD_PATH, "r");

    int i = 1;

    while (fgets(buffer, BUFFER_SIZE, fp)) {

        if (strcmp(buffer, "") == 0) break;
        if (i > CACHE_SIZE) break;
        i++;

        string *record = split(buffer, " ");
        record->str[3][strlen(record->str[3]) - 1] = '\0';
        put(cache, strdup(record->str[0]), strdup(record->str[3]));
    }

    fclose(fp);
}

void get_in_file(char *key, LRUCache *cache) {

    printf("Searching %s in file\n", key);

    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(RECORD_PATH, "r");

    while (fgets(buffer, BUFFER_SIZE, fp)) {

        string *record = split(buffer, " ");

        if (strcmp(record->str[0], key) == 0) {

            record->str[3][strlen(record->str[3]) - 1] = '\0';
            put(cache, strdup(record->str[0]), strdup(record->str[3]));
            break;
        }
    }

    fclose(fp);
}
