#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bitmap.h"
#include "filters.h"


int main() {

    char *file_out = strdup("../src/lab3/images/out.bmp");

    char *file_in = malloc(0);
    printf("Input file:");
    gets(file_in);
    if (!file_in) return 0;
    Bitmap *image = new_bitmap(file_in);

    read_pixels(image, file_in);


    while (1) {
        int inp;
        printf("1. Grayscale\n2. Invert colors\n3. Gamma correction\n4. Median filter\n0. Exit\n");
        while (!scanf("%d", &inp) || inp > 4 || inp < 0 || getchar() != '\n') {
            printf("Wrong input! Enter again:");
            rewind(stdin);
        }

        if (inp == 0) return 1;
        else if (inp == 1) grayscale_filter(image);
        else if (inp == 2) invert_filter(image);
        else if (inp == 3) gamma_correction(image);
        else if (inp == 4) median_filter(image);
        write_bitmap(image, file_out);

        printf("\n");

    }
}