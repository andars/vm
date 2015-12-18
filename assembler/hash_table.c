#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"

struct ht_entry {
    char* key;
    void* value;
    int size;
    ht_entry* next;
};

struct hash_table {
    int num_buckets;
    int num_entries;
    ht_entry** table;
};

static unsigned long fnv1_a(void* input, unsigned long length) {
    unsigned char* data = (unsigned char*) input;
    unsigned long hash = 14695981039346656036UL;
    for (unsigned long i = 0; i<length; i++) {
        hash = hash ^ data[i];
        hash = hash * 1099511628211L;
    }

    return hash;
}

static int get_index(char* key, int size) {
    unsigned long hash = fnv1_a(key, strlen(key));
    int i = (int) (hash % size);
    return i;
}

hash_table* ht_create() {
    hash_table* ht = malloc(sizeof(*ht));
    if (ht == NULL) {
        fprintf(stderr, "failed to allocate memory");
        abort();
    }
    ht->num_buckets = 64;
    ht->num_entries = 0;
    ht->table = calloc(sizeof(ht_entry*), ht->num_buckets);
    if (ht->table == NULL) {
        fprintf(stderr, "failed to allocate memory");
        abort();
    }
    return ht;
}

void ht_set(hash_table* ht, char* key, void* value) { 
    int index = get_index(key, ht->num_buckets);
    ht_entry* current = ht->table[index];
    if (current != NULL) {
        while (current != NULL && strcmp(current->key, key) != 0) {
            current=current->next;
        }
        if (current == NULL) { //collision occurred & this key is new
            current = malloc(sizeof(*current));
            current->key = strdup(key);
            current->next = NULL;
            ht->num_entries++;
        }
        free(current->value);
        current->value = value;
    } else {
        current = malloc(sizeof(*current));
        ht->table[index] = current;
        if (current == NULL) {
            fprintf(stderr, "failed to allocate memory");
            abort();
        }
        current->key = strdup(key);
        current->next = NULL;    
        current->value = value;   
        ht->num_entries++;
    }
}

void* ht_get(hash_table* ht, char* key) {
    int index = get_index(key, ht->num_buckets);
    ht_entry* current = ht->table[index];

    while (current != NULL && strcmp(current->key, key) != 0) {
        printf("not at this link, instead found %s\n", current->key);
        current = current->next;
    }

    if (current == NULL) return NULL;
    return current->value;
}
