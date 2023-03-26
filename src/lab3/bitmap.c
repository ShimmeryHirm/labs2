#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


Bitmap *new_bitmap(char *filename) {

    Bitmap *bitmap = malloc(sizeof(Bitmap));
    BitmapFileHeader *file_header;
    BitmapInfoHeader *info_header;
    unsigned char *pixel_array = NULL;

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error opening file");
        return NULL;
    }

    file_header = malloc(sizeof(BitmapFileHeader));
    fread(file_header, sizeof(BitmapFileHeader), 1, fp);

    if (file_header->header1 == 'B' && file_header->header2 == 'M') {
        info_header = malloc(sizeof(BitmapInfoHeader));
        fread(info_header, sizeof(BitmapInfoHeader), 1, fp);
    } else {
        printf("Not  valid bmp file.");
        return NULL;
    }
    fclose(fp);

    bitmap->file_header = file_header;
    bitmap->info_header = info_header;
    bitmap->pixel_array = pixel_array;

    return bitmap;
}

void read_pixels(Bitmap *bitmap, char *filename) {

    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;
    int padding = get_padding(width);
    unsigned int offset = bitmap->file_header->pixel_array_offset;

    FILE *fp = fopen(filename, "rb");

    fseek(fp, offset, SEEK_SET);

    unsigned char *pixel_array = malloc(width * height * 3);

    for (int row = 0; row < height; row++) {
        fread(&pixel_array[row * (width * 3)], sizeof(unsigned char) * 3, width, fp);

        unsigned char padding_byte;
        for (int p = 0; p < padding; p++) {
            fread(&padding_byte, sizeof(unsigned char), 1, fp);
        }
    }

    fclose(fp);
    bitmap->pixel_array = pixel_array;
}


void write_bitmap(Bitmap *bitmap, char *fileout) {
    FILE *fp = fopen(fileout, "wb");

    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;

    int padding = get_padding(width);

    fwrite(bitmap->file_header, sizeof(BitmapFileHeader), 1, fp);
    fwrite(bitmap->info_header, sizeof(BitmapInfoHeader), 1, fp);

    unsigned char *pixel_array = bitmap->pixel_array;

    for (int row = 0; row < height; row++) {
        fwrite(&pixel_array[row * (width * 3)], sizeof(unsigned char) * 3, width, fp);

        for (int p = 0; p < padding; p++) {
            unsigned char null = 0;
            fwrite(&null, sizeof(unsigned char), 1, fp);
        }
    }

    fclose(fp);
}

int get_padding(int width) {

    int padding = 0;
    if ((width * 3) % 4 != 0) {
        padding = 4 - ((width * 3) % 4);
    }

    return padding;
}


Pixel *get_pixel(Bitmap *bitmap, int row, int col) {
    Pixel *pixel = NULL;
    int width = bitmap->info_header->width;
    int height = bitmap->info_header->height;


    if (col >= width) {
        col = width - (col % width);
    } else if (col < 0) {
        col = -col;
    }

    if (row >= height) {
        row = height - (row % height);
    } else if (row < 0) {
        row = -row;
    }

    pixel = (Pixel *) &(bitmap->pixel_array[row * (width * 3) + (col * 3)]);

    return pixel;
}