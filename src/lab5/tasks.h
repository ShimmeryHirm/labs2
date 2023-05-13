#ifndef OAIP_LABS2_TASKS_H
#define OAIP_LABS2_TASKS_H

#include "cache.h"

char *find_ip_by_domain(LRUCache *cache, char *key);

void add_record();

void find_domains_by_ip();

#endif //OAIP_LABS2_TASKS_H
