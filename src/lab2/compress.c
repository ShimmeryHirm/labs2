#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compress.h"


int check(Node *head, char *word) {
    while (head) {
        if (strcmp(head->word, word) == 0) return 1;
        head = head->next;
    }
    return 0;
}


int count_profit(Node *a, Node *b) {
    if (a->count <= b->count) return -0;
    else if (a->used || b->used) return -1;
    else
        return (a->count * a->len + b->count * b->len) - (a->count * b->len + b->count * a->len) -
               (b->len + a->len + 2);

}

void mark_used(Node *head, char *word) {
    while (head) {
        if (strcmp(head->word, word) == 0) {
            head->used = 1;
            return;
        }
        head = head->next;
    }
}

void replace_words(Node *head, string *split_text, char *file_name) {
    Node *a = head;

    char *data_name = calloc(strlen(file_name) + 10, sizeof(char));
    strcat(strcat(data_name, file_name), ".data");
    fclose(fopen(data_name, "w"));

    while (a) {
        int max = 0;
        char *word;
        Node *b = head;
        while (b) {
            int profit = count_profit(a, b);
            if (profit > max) {
                max = profit;
                word = b->word;
            }

            b = b->next;
        }

        if (max > 0) {
            mark_used(head, a->word);
            mark_used(head, word);

            if (strlen(word) == 0 || strlen(a->word) == 0) continue;
            swap_words(split_text, a->word, word);
            FILE *fp = fopen(data_name, "ab");
            if (fp == NULL) exit(0);

            fputs(a->word, fp);
            fputs(" ", fp);
            fputs(word, fp);
            fputs("\n", fp);
            fclose(fp);
        }
        a = a->next;
    }
}

void count_repeats(string *split_text, Node **head) {

    for (int i = 0; i < split_text->len; i++) {

        if (check(*head, split_text->str[i])) continue;
        if (strstr(split_text->str[i], "\n") != NULL) continue;
        int cnt = 0;
        for (int j = 0; j < split_text->len; j++) {
            if (strcmp(split_text->str[i], split_text->str[j]) == 0) {
                cnt++;
            }
        }
        pushBack(&(*head), split_text->str[i], cnt);
    }
    mergeSort(&(*head));
}

void compress(char file_name[]) {

    char *text = file_read(file_name);
    if (text == NULL) exit(0);

    FILE *fp = fopen(file_name, "rb");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    printf("Size: %d\n", size);

    string *split_text = split(text, " ");

    Node *head = NULL;
    count_repeats(split_text, &head);

    replace_words(head, split_text, file_name);

    char *compressed_name = calloc(strlen(file_name) + 10, sizeof(char));
    strcat(strcat(compressed_name, file_name), ".compressed");
    fclose(fopen(compressed_name, "w"));
    fp = fopen(compressed_name, "ab");
    if (fp == NULL) exit(0);
    for (int i = 0; i < split_text->len; i++) {
        fputs(split_text->str[i], fp);
        if (i != split_text->len - 1) fputs(" ", fp);
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    printf("New size: %d\n", size);
    fclose(fp);

    char *data_name = calloc(strlen(file_name) + 10, sizeof(char));
    strcat(strcat(data_name, file_name), ".data");

    fp = fopen(data_name, "rb");
    fseek(fp, 0L, SEEK_END);
    int data_size = ftell(fp);
    printf("Data size: %d\n", data_size);
    printf("Total size: %d\n", size + data_size);
    printf("File compressed!\n");


}