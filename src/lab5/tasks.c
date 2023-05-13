#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "cache.h"
#include "config.h"


char *find_ip_by_domain(LRUCache *cache, char *key) {

    char *record = get(cache, key);

    if (!record) {
        get_in_file(key, cache);
        record = get(cache, key);

        if (!record) return NULL;
    }

    if (is_ip(strdup(record))) return record;
    else record = find_ip_by_domain(cache, record);

    return record;
}

void add_record() {

    printf("Input record:\n");

    char *record = calloc(1, BUFFER_SIZE);
    gets(record);
    string *split_record = split(strdup(record), " ");

    if (!is_ip(strdup(split_record->str[3])) && !strstr(strdup(record), "CNAME")) {
        return;
    }

    char *text = file_read(RECORD_PATH);
    if (strstr(text, record)) {
        printf("Record already in file\n");
        return;
    }

    FILE *fp = fopen(RECORD_PATH, "a");
    fputs(record, fp);
    fputs("\n", fp);
    fclose(fp);

    printf("Record added\n");
}


void find_domains_by_ip() {

    printf("Input ip:\n");

    char *ip = calloc(1, BUFFER_SIZE);
    gets(ip);

    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(RECORD_PATH, "r");

    while (fgets(buffer, BUFFER_SIZE, fp)) {

        string *record = split(buffer, " ");
        record->str[3][strlen(record->str[3]) - 1] = '\0';

        if (strcmp(record->str[3], ip) == 0) printf("%s\n", record->str[0]);
    }
}
