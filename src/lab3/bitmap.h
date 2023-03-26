#ifndef BITMAP_H
#define BITMAP_H

#pragma pack(push, 1)

typedef struct {

    unsigned char header1;
    unsigned char header2;
    unsigned int bmp_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixel_array_offset;
} BitmapFileHeader;

typedef struct {

    unsigned int infoheader_size;
    int width;
    int height;
    unsigned short color_planes;
    unsigned short bits_per_pixel;
    unsigned int compression_method;
    unsigned int image_size;
    unsigned int h_res;
    unsigned int v_res;
    unsigned int color_palette;
    unsigned int important_colors;
} BitmapInfoHeader;

#pragma pack(pop)

typedef struct {
    BitmapFileHeader *file_header;
    BitmapInfoHeader *info_header;
    unsigned char *pixel_array;
} Bitmap;

typedef struct {
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Pixel;

int get_padding(int width);

Bitmap *new_bitmap(char *filename);

void read_pixels(Bitmap *bitmap, char *filename);

void write_bitmap(Bitmap *bitmap, char *fileout);

Pixel *get_pixel(Bitmap *bitmap, int row, int col);

#endif