#ifndef HASH_TABLE_H
#define HASH_TABLE_H

struct ht_entry;
typedef struct ht_entry ht_entry;

struct hash_table;
typedef struct hash_table hash_table;


hash_table* ht_create();
void ht_set(hash_table* ht, char* key, void* value);
void* ht_get(hash_table* ht, char* key);
void ht_destroy(hash_table* ht);

#endif
