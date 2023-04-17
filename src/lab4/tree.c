#include "tree.h"
#include <string.h>
#include <stdlib.h>

Node *create_node(char *data) {

    Node *node = (Node *) malloc(sizeof(Node));

    node->data = strdup(data);
    node->yes = NULL;
    node->no = NULL;

    return node;
}

Node *add_branch() {

    printf("What it is?\n");
    char res[100];
    gets(res);

    printf("What is the difference?\n");
    char data[100];
    gets(data);

    Node *new_node = create_node(data);
    new_node->yes = create_node(res);
    return new_node;
}

Node *read_tree(FILE *fp) {

    char data[100];
    fgets(data, sizeof(data), fp);
    data[strlen(data) - 1] = '\0';

    if (data[0] == '/') return NULL;

    Node *node = create_node(data);

    node->yes = read_tree(fp);
    node->no = read_tree(fp);

    return node;

}

void write_tree(Node *node, FILE *fp) {

    if (node == NULL) {
        fputs("/\n", fp);
        return;
    }

    fputs(node->data, fp);
    fputs("\n", fp);
    write_tree(node->yes, fp);
    write_tree(node->no, fp);

}

void dot(Node *node, FILE *fp) {

    if (node) {
        if (node->yes != NULL) fprintf(fp, "\"%s\"-> \"%s\"\n", node->data, node->yes->data);
        dot(node->yes, fp);
        if (node->no != NULL) fprintf(fp, "\"%s\"-> \"%s\"\n", node->data, node->no->data);
        dot(node->no, fp);
    }

}

void diagram(Node *node) {
    FILE *fp = fopen("../src/lab4/files/tree.dot", "w");
    fputs("digraph G {\n", fp);
    dot(node, fp);
    fputs("}\n", fp);
    fclose(fp);

    char command[256];
    snprintf(command, sizeof(command), "%s -Tsvg ../src/lab4/files/tree.dot > ../src/lab4/files/tree.svg", DOT_PATH);
    system(command);
}