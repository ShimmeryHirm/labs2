#include <stdio.h>

#include "compress.h"
#include "decompress.h"


int main() {
    char file_name[] = "../src/lab2/files/text.txt";
    while (1) {

        int c;
        printf("1. Compress\n2. Decompress\n3. Exit\n");
        scanf("%d", &c);

        if (c == 1) compress(file_name);
        if (c == 2) decompress(file_name);
        if (c == 0) return 0;
        printf("\n");
    }

}