#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

char *multi_tok(char *input, char *delimiter) {
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
        return string;

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}

string *split(char *input, char *delimiter) {

    string *str = malloc(sizeof(string));
    str->str = NULL;
    str->len = 0;

    char *token = multi_tok(input, delimiter);

    while (token != NULL) {
        str->str = realloc(str->str, (str->len + 1) * sizeof(char *));
        str->str[str->len++] = token;

        token = multi_tok(NULL, delimiter);
    }
    return str;
}
void swap_words(string *text, char *word1, char *word2) {
    for (int i = 0; i < text->len; i++) {
        if (strcmp(text->str[i], word1) == 0) {
            text->str[i] = word2;
        } else if (strcmp(text->str[i], word2) == 0) {
            text->str[i] = word1;
        }
    }
}


char *file_read(char path[]) {

    long length;
    FILE *f = fopen(path, "rb");

    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = calloc(length, 1);

    fread(buffer, 1, length, f);
    fclose(f);

    return buffer;
}