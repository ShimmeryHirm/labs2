
#include <math.h>
#include <stdio.h>
#include "filters.h"

void invert_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            // Invert all the bytes

            pixel->b = ~(pixel->b);
            pixel->g = ~(pixel->g);
            pixel->r = ~(pixel->r);
        }
    }
}

void gamma_correction(Bitmap *bitmap) {

    float gamma;
    printf("Input gamma coefficient:");
    scanf("%f", &gamma);

    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);

            pixel->b = pow(pixel->b / 255.0, gamma) * 255.0;
            pixel->g = pow(pixel->g / 255.0, gamma) * 255.0;
            pixel->r = pow(pixel->r / 255.0, gamma) * 255.0;
        }
    }
}

void grayscale_filter(Bitmap *bitmap) {
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Pixel *pixel = get_pixel(bitmap, row, col);


            int n = 0.3 * pixel->r + 0.6 * pixel->g + 0.1 * pixel->b;
            pixel->b = n;
            pixel->g = n;
            pixel->r = n;

        }
    }

}


void median_filter(Bitmap *bitmap) {
    Pixel *temp[9];
    int count;
    int i, j, k, l;
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;
    for (i = 1; i < height - 1; i++) {
        for (j = 1; j < width - 1; j++) {
            count = 0;
            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    temp[count] = get_pixel(bitmap, i + k, j + l);
                    count++;
                }
            }
            for (k = 0; k < 9; k++) {
                for (l = k + 1; l < 9; l++) {
                    if (temp[k]->r > temp[l]->r) {
                        Pixel *t = temp[k];
                        temp[k] = temp[l];
                        temp[l] = t;
                    }
                }
            }

            Pixel *p = get_pixel(bitmap, i, j);
            p->r = temp[4]->r;
            p->g = temp[4]->g;
            p->b = temp[4]->b;

        }
    }
}