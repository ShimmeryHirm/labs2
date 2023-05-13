#ifndef OAIP_LABS2_CACHE_H
#define OAIP_LABS2_CACHE_H

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
    struct Node *prev;
    struct Node *collision_chain;
} Node;

typedef struct Table {
    int capacity;
    Node **array;
} Table;

typedef struct List {
    int size;
    int capacity;
    Node *head;
    Node *tail;
} List;

typedef struct LRUCache {
    Table *table;
    List *list;
} LRUCache;

Node *create_node(char *key, char *value);

Table *create_table(int capacity);

LRUCache *create_cache(int size);

static size_t get_hash_index(Table *table, const char *source);

void remove_oldest(LRUCache *cache);

void move_to_front(LRUCache *cache, char *key);

void add_to_list(LRUCache *cache, Node *node);

int add_to_table(Table *table, Node *node);

void put(LRUCache *cache, char *key, char *value);

char *get(LRUCache *cache, char *key);

void print_cache(LRUCache *cache);

#endif //OAIP_LABS2_CACHE_H
