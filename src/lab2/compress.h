#ifndef OAIP_LABS2_COMPRESS_H
#define OAIP_LABS2_COMPRESS_H

#include "linked_lists.h"
#include "utils.h"

int check(Node *head, char *word);

int count_profit(Node *a, Node *b);

void mark_used(Node *head, char *word);

void replace_words(Node *head, string *split_text, char *file_name);

void count_repeats(string *split_text, Node **head);

void compress(char file_name[]);

#endif //OAIP_LABS2_COMPRESS_H
