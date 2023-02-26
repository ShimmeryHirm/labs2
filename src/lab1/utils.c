#include "utils.h"

int startswith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}


string *split(char *input, char *delimiter) {
    int targetsize = 0;
    string *str = malloc(sizeof(string));


    str->str = NULL;
    str->len = 0;
    char *pos;
    char *oldpos = input;
    int newsize;
    int dlen = strlen(delimiter);
    do {
        pos = strstr(oldpos, delimiter);
        if (pos) {
            newsize = pos - oldpos;
        } else {
            newsize = strlen(oldpos);
        }
        char *newstr = malloc(sizeof(char) * (newsize + 1));
        strncpy(newstr, oldpos, newsize);
        newstr[newsize] = '\0';
        oldpos = pos + dlen;
        str->str = realloc(str->str, (targetsize + 1) * sizeof(char *));
        str->str[targetsize++] = newstr;
        str->len++;
    } while (pos != NULL);
    return str;
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