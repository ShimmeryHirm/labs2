#ifndef OAIP_LABS2_TREE_H
#define OAIP_LABS2_TREE_H

#include <stdio.h>
#define DOT_PATH "C:\\Users\\shh\\Desktop\\Graphviz\\bin\\dot"

typedef struct Node {

    char *data;
    struct Node *yes;
    struct Node *no;

} Node;

Node *create_node(char *data);

Node *add_branch();

Node *read_tree(FILE *fp);

void write_tree(Node *node, FILE *fp);

void dot(Node *node, FILE *fp);

void diagram(Node *node);

#endif //OAIP_LABS2_TREE_H
