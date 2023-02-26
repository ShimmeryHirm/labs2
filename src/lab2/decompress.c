#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void decompress(char file_name[]) {

    char *compressed_name = calloc(strlen(file_name) + 10, sizeof(char));
    strcat(strcat(compressed_name, file_name), ".compressed");
    char *text = file_read(compressed_name);
    if (text == NULL) exit(0);
    string *compressed_text = split(text, " ");

    FILE *fp = fopen(compressed_name, "r");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    printf("Size: %d\n", size);

    char *data_name = calloc(strlen(file_name) + 10, sizeof(char));
    strcat(strcat(data_name, file_name), ".data");
    text = file_read(data_name);
    if (text == NULL) exit(0);
    string *compressed_data = split(text, "\n");


    for (int i = 0; i < compressed_data->len; i++) {
        string *words = split(compressed_data->str[i], " ");
        if (words->len != 2) continue;
        swap_words(compressed_text, words->str[0], words->str[1]);
    }

    // for (int i = 0; i < compressed_text->len; i++) {
    //     printf("%s ", compressed_text->str[i]);
    // }

    char *decompressed_name = calloc(strlen(file_name) + 10, sizeof(char));
    strcat(strcat(decompressed_name, file_name), ".decompressed");

    fclose(fopen(decompressed_name, "w"));

    fp = fopen(decompressed_name, "a");
    if (fp == NULL) exit(0);

    for (int i = 0; i < compressed_text->len; i++) {
        fputs(compressed_text->str[i], fp);
        if (i != compressed_text->len - 1) fputs(" ", fp);
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fclose(fp);

    printf("New size: %d\n", size);
    printf("File decompressed!\n");
}
