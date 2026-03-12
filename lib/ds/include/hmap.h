#ifndef H_MAP
#define H_MAP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Hashmap implementation Key -> value
 * 
 */

/*
 * TODO: implement remove function and print function passing 
 * a parameter a function used to print a single element
 */

#define INIT_SIZE 8
#define THRESHOLD 0.7 // if the size is at 70% of the cap, resize it

typedef enum hm_state_e {
    EMPTY   = 0,
    USED    = 1,
    DELETED = 2
} hm_state_t;

typedef enum hm_dt_e {
    INT     = 0,
    STRING  = 1
} hm_dt_t;

typedef struct hm_entry_s {
    void *key;
    void *value;
    hm_state_t tombstone;

} hm_entry_t;

typedef struct hm_map_s {
    hm_entry_t *entries;
    size_t count;
    size_t size;
    size_t key_size;
    size_t value_size;
    hm_dt_t dt;

    // function to compare keys
    int (*cmp)(const void *, const void *);
} hm_map_t;

int hm_init(
    hm_map_t *const hmap, const size_t key_size, const size_t value_size,
    const hm_dt_t dt, int (*cmp)(const void *, const void *));
int hm_put(hm_map_t *const hmap, const void *key, const void *value);
void *hm_get(hm_map_t *const hmap, const void *key);
size_t hm_hash_i(const void *key, const size_t k_size, const size_t size);
size_t hm_hash_s(const void *key, const size_t k_size, const size_t size);
int hm_resize(hm_map_t *const hmap);
int hm_free(hm_map_t *hmap);


#endif /* H_MAP */
