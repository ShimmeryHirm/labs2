#include "sort.h"

int comp_name(item *a, item *b) {
    return strcmp(a->name, b->name);
}

int comp_price(item *a, item *b) {

    return (a->price > b->price) - (a->price < b->price);
}

int comp_quality(item *a, item *b) {
    return a->quality - b->quality;
}

int cmp_qty_qlty(const item *a, const item *b) {

    if (b->quality < a->quality) {
        return 1;
    } else if (a->quality < b->quality) {
        return -1;
    } else {
        return (b->quantity < a->quantity) - (a->quantity < b->quantity);
    }
}

int cmp_name_price(const item *a, const item *b) {
    if ((a->price > b->price) - (a->price < b->price) != 0) {
        return (a->price > b->price) - (a->price < b->price);
    } else {
        return strcmp(a->name, b->name);
    }
}