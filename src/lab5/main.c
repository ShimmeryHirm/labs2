#include<stdio.h>
#include<stdlib.h>

#include "utils.h"
#include "cache.h"
#include "config.h"
#include "tasks.h"


int main() {

    LRUCache *cache = create_cache(CACHE_SIZE);
    fill_cache(cache);

    while (1) {
        printf("1. Find IP by domain\n2. Find domain by IP\n3. Add record\n4. Print cache\n");
        int c;
        scanf("%d", &c);
        rewind(stdin);

        if (c == 1) {

            printf("Input domain: ");
            char *domain = calloc(1, BUFFER_SIZE);
            gets(domain);

            char *res = find_ip_by_domain(cache, domain);
            if (res) printf("%s", res);
            else printf("Record not found");

        } else if (c == 2) find_domains_by_ip();
        else if (c == 3) add_record();
        else if (c == 4) print_cache(cache);
        else if (c == 0) return 0;
        else continue;
        printf("\n");

    }
}