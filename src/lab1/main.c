#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "utils.h"


const char *const item_quality_str[] =
        {
                [unique] = "unique",
                [inscribed] = "inscribed",
                [autographed]  = "autographed",
                [corrupted]  = "corrupted",
        };

item *parse_html(char *path, int *len) {

    char *doc = file_read(path);
    if (doc == NULL) exit(0);

    string *str = split(doc, "market_listing_row_link");

    *len = str->len - 1;
    item *arr = calloc(*len, sizeof(item));

    for (int i = 1; i < str->len; i++) {

        arr[i - 1].name = split(split(split(str->str[i], "class=\"market_listing_item_name\" ")->str[1], "\">")->str[1],
                                "<")->str[0];

        if (startswith("Autographed ", arr[i - 1].name)) {
            arr[i - 1].quality = autographed;
        } else if (startswith("Inscribed ", arr[i - 1].name)) {
            arr[i - 1].quality = inscribed;
        } else if (startswith("Corrupted ", arr[i - 1].name)) {
            arr[i - 1].quality = corrupted;
        } else {
            arr[i - 1].quality = unique;
        }

        arr[i - 1].quantity = atoi(split(split(str->str[i], "data-qty=\"")->str[1], "\">")->str[0]);
        arr[i - 1].price = atof(split(split(str->str[i], "$")->str[1], " USD")->str[0]);

    }
    return arr;

};

void print_items(item *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d. %s Quantity: %d Price: %.2f$. Quality: %s.\n", i + 1, arr[i].name, arr[i].quantity,
               arr[i].price,
               item_quality_str[arr[i].quality]);
    }
}

void add_item(item *arr, int *len) {
    char *it = malloc(0);
    printf("Input item [name/quantity/price]: ");
    rewind(stdin);
    gets(it);


    string *str = split(it, "/");

    if (str->len < 3) {
        printf("Not enough data\n");
        return;
    }
    ++(*len);

    arr[*len - 1].name = str->str[0];
    if (startswith("Autographed ", str->str[0])) {
        arr[*len - 1].quality = autographed;
    } else if (startswith("Inscribed ", str->str[0])) {
        arr[*len - 1].quality = inscribed;
    } else if (startswith("Corrupted ", str->str[0])) {
        arr[*len - 1].quality = corrupted;
    } else {
        arr[*len - 1].quality = unique;
    }

    arr[*len - 1].quantity = atoi(str->str[1]);
    arr[*len - 1].price = atof(str->str[2]);
}


void remove_item(item *arr, int *len) {
    char *name = malloc(0);
    printf("Input name: ");
    rewind(stdin);
    gets(name);

    for (int i = 0; i < *len; i++) {
        if (!strcmp(arr[i].name, name)) {

            for (int j = i; j < *len - 1; j++) {
                arr[j] = arr[j + 1];
            }
            (*len)--;
            break;
        }
    }
}


void sort(item *arr, int len) {
    printf("1. Name\n2. Price\n3. Quality\n4. Name and Price\n5. Quality and Quantity\n0. Exit\n");
    int inp;
    while (!scanf("%d", &inp) || inp > 5 || inp < 0 || getchar() != '\n') {
        printf("Wrong input! Enter again:");
        rewind(stdin);
    }
    if (inp == 0) return;
    if (inp == 1) qsort(arr, len, sizeof(item), (int (*)(const void *, const void *)) comp_name);
    if (inp == 2) qsort(arr, len, sizeof(item), (int (*)(const void *, const void *)) comp_price);
    if (inp == 3) qsort(arr, len, sizeof(item), (int (*)(const void *, const void *)) comp_quality);
    if (inp == 4) qsort(arr, len, sizeof(item), (int (*)(const void *, const void *)) cmp_name_price);
    if (inp == 5) qsort(arr, len, sizeof(item), (int (*)(const void *, const void *)) cmp_qty_qlty);


}


int main() {

    int len;
    item *arr = parse_html("../lab1/page.html", &len);
    while (1) {
        int inp;
        printf("1. Print items\n2. Add item\n3. Remove item\n4. Sort\n0. Exit\n");
        while (!scanf("%d", &inp) || inp > 4 || inp < 0 || getchar() != '\n') {
            printf("Wrong input! Enter again:");
            rewind(stdin);
        }

        if (inp == 0) return 1;
        else if (inp == 1) print_items(arr, len);
        else if (inp == 2) add_item(arr, &len);
        else if (inp == 3) remove_item(arr, &len);
        else if (inp == 4) sort(arr, len);

        printf("\n");
    }
}