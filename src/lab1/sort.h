//
// Created by shh on 12.02.2023.
//

#ifndef OAIP_LABS2_SORT_H
#define OAIP_LABS2_SORT_H


#include <string.h>
#include "utils.h"

int comp_name(item *a, item *b);

int comp_price(item *a, item *b);

int comp_quality(item *a, item *b);

int cmp_qty_qlty(const item *a, const item *b);

int cmp_name_price(const item *a, const item *b);


#endif //OAIP_LABS2_SORT_H
