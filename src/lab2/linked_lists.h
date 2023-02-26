#ifndef OAIP_LABS2_LINKED_LISTS_H
#define OAIP_LABS2_LINKED_LISTS_H

typedef struct Node {
    char *word;
    int count;
    int len;
    int used;
    struct Node *next;
} Node;

Node *getLast(Node *head);

void pushBack(Node **head, char *word, int count);

void merge(Node *a, Node *b, Node **c);

void split_linked_list(Node *src, Node **low, Node **high);

void mergeSort(Node **head);

#endif //OAIP_LABS2_LINKED_LISTS_H
