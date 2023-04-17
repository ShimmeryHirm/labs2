#include <string.h>
#include <stdio.h>
#include "tree.h"


void ask(Node *node) {

    printf("%s\n", node->data);

    char input;
    scanf("%c", &input);
    rewind(stdin);

    if (input == 'y') {

        if (node->yes == NULL) {
            printf("Ez\n");
            return;
        }

        node = node->yes;
    } else {

        if (node->no == NULL) {
            memcpy(node, add_branch(), sizeof(Node));
            return;
        }

        node = node->no;
    }

    ask(node);

}



int main() {


    while (1) {

        FILE *fp = fopen("../src/lab4/files/tree.txt", "r");
        Node *node = read_tree(fp);
        fclose(fp);
        diagram(node);

        printf("Answer the questions:\n");
        ask(node);

        fp = fopen("../src/lab4/files/tree.txt", "w");
        write_tree(node, fp);
        fclose(fp);
    }

}