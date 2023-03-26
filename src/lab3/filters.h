
#ifndef OAIP_LABS2_FILTERS_H
#define OAIP_LABS2_FILTERS_H

#include "bitmap.h"

void median_filter(Bitmap *bitmap);

void grayscale_filter(Bitmap *bitmap);

void gamma_correction(Bitmap *bitmap);

void invert_filter(Bitmap *bitmap);

#endif //OAIP_LABS2_FILTERS_H
