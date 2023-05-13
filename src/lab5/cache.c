#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

Node *create_node(char *key, char *value) {

    Node *node = (Node *) malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    node->collision_chain = NULL;

    return node;
}

List *create_list(int capacity) {

    List *list = (List *) malloc(sizeof(List));

    list->size = 0;
    list->capacity = capacity;
    list->head = list->tail = NULL;

    return list;
}

Table *create_table(int capacity) {

    Table *hash = (Table *) malloc(sizeof(Table));

    hash->capacity = capacity;
    hash->array = (Node **) malloc(sizeof(Node) * capacity);
    for (int i = 0; i < capacity; i++) hash->array[i] = NULL;

    return hash;
}

LRUCache *create_cache(int size) {

    LRUCache *cache = (LRUCache *) malloc(sizeof(LRUCache));
    Table *table = create_table(size * 2);
    List *list = create_list(size);
    cache->table = table;
    cache->list = list;

    return cache;
}

static size_t get_hash_index(Table *table, const char *str) {

    if (str == NULL)
        return 0;

    size_t hash = 0;
    int c;
    while ((c = *str++)) {
        hash = (hash * 33) + c;
    }

    return hash % table->capacity;
}

void remove_oldest(LRUCache *cache) {

    Table *table = cache->table;
    List *list = cache->list;

    Node *entry = list->head;

    if (list->head == NULL)
        return;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = entry->next;
        list->size = list->size - 1;
        list->head->prev = NULL;
    }

    size_t index = get_hash_index(table, entry->key);
    Node **node = &table->array[index];
    while ((*node) != entry)
        node = &(*node)->next;
    *node = entry->next;

    free(entry);
}

void move_to_front(LRUCache *cache, char *key) {

    Table *table = cache->table;
    List *list = cache->list;

    if (list->size == 1)
        return;

    size_t index = get_hash_index(table, key);
    Node *curr = table->array[index];

    while (curr) {
        if (strcmp(curr->key, key) == 0) break;
        curr = curr->collision_chain;
    }

    if (curr == NULL)
        return;

    if (curr->prev == NULL) {
        curr->prev = list->tail;
        list->head = curr->next;
        list->head->prev = NULL;
        list->tail->next = curr;
        list->tail = curr;
        list->tail->next = NULL;
        return;
    }

    if (curr->next == NULL)
        return;

    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    curr->next = NULL;
    list->tail->next = curr;
    curr->prev = list->tail;
    list->tail = curr;
}

void add_to_list(LRUCache *cache, Node *node) {

    List *list = cache->list;

    if (list->size == list->capacity) remove_oldest(cache);

    if (list->head == NULL) {
        list->head = list->tail = node;
        list->size = 1;
        return;
    }

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->size = list->size + 1;
}

int add_to_table(Table *table, Node *node) {

    size_t index = get_hash_index(table, node->key);
    if (table->array[index] != NULL) {

        Node *curr = table->array[index];

        while (curr->collision_chain != NULL) {
            if (strcmp(curr->key, node->key) == 0) {
                curr->value = node->value;
                return 1;
            }
            curr = curr->collision_chain;
        }

        if (strcmp(curr->key, node->key) == 0) {
            curr->value = node->value;
            return 1;
        }

        curr->collision_chain = node;
        return 0;
    } else {
        table->array[index] = node;
        return 0;
    }
}

void put(LRUCache *cache, char *key, char *value) {

    Node *node = create_node(key, value);

    if (add_to_table(cache->table, node)) move_to_front(cache, node->key);
    else add_to_list(cache, node);
}

char *get(LRUCache *cache, char *key) {

    Table *table = cache->table;
    size_t index = get_hash_index(table, key);
    Node *curr = table->array[index];

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            move_to_front(cache, key);
            return curr->value;
        }
        curr = curr->collision_chain;
    }

    return NULL;
}

void print_cache(LRUCache *cache) {

    Node *temp = cache->list->head;
    for (int i = 0; i < cache->list->size; i++) {
        printf("%s %s \n", temp->key, temp->value);
        temp = temp->next;
    }
}