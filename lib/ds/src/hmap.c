#include "../include/hmap.h"

int hm_init(
    hm_map_t *const hmap, const size_t key_size, const size_t value_size,
    const hm_dt_t dt, int (*cmp)(const void *, const void *)) {

    hmap->count = 0;
    hmap->size = INIT_SIZE;
    hmap->key_size = key_size;
    hmap->value_size = value_size;
    hmap->dt = dt;
    hmap->cmp = cmp;

    hmap->entries = malloc(hmap->size * sizeof(hm_entry_t));

    if (hmap->entries == NULL) {
        fprintf(stderr, "Failed to allocte memory\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < hmap->size; i++) {
        hmap->entries[i].key = malloc(hmap->key_size);
        hmap->entries[i].value = malloc(hmap->value_size);
        hmap->entries[i].tombstone = EMPTY;
    }

    return EXIT_SUCCESS;
}

int hm_put(hm_map_t *const hmap, const void *key, const void *value) {
    if ((float)hmap->size * THRESHOLD <= (float)hmap->count) {
        // resize the hmap
        hm_resize(hmap);
    }

    size_t index = -1;

    switch (hmap->dt) {
        case INT:
            index = hm_hash_i(key, hmap->key_size, hmap->size);
            break;
        case STRING:
            index = hm_hash_s(key, hmap->key_size, hmap->size);
            break;
        default:
            fprintf(stderr, "Incorrect datatype\n");
            break;
    }

    hm_entry_t *entry = &(hmap->entries[index]); 
    while (entry->tombstone == USED) {
        if (hmap->cmp(key, entry->key) == 0) {
            // key exists
            hmap->count--;
            break;
        }

        index = (index + 1) % hmap->size;
        entry = &(hmap->entries[index]);
    }

    memcpy(entry->key, key, hmap->key_size);
    memcpy(entry->value, value, hmap->value_size);
    entry->tombstone = USED;

    hmap->count++;

    return EXIT_SUCCESS;
}

// O(1)
void *hm_get(hm_map_t *const hmap, const void *key) {
    size_t index = -1;

    switch (hmap->dt) {
        case INT:
            index = hm_hash_i(key, hmap->key_size, hmap->size);
            break;
        case STRING:
            index = hm_hash_s(key, hmap->key_size, hmap->size);
            break;
        default:
            fprintf(stderr, "Incorrect datatype\n");
            break;
    }

    size_t start = index;

    while (hmap->entries[index].tombstone != EMPTY) {
        if (hmap->entries[index].tombstone == USED) {
            if (hmap->cmp(key, hmap->entries[index].key) == 0) {
                // key found, return the value
                return hmap->entries[index].value;
            }
        }

        index = (index + 1) % hmap->size;
        if (index == start) {
            // key not found
            break;
        }
    }

    return NULL;
}

// algoritmo djb2 for integers
size_t hm_hash_i(const void *key, const size_t k_size, const size_t size) {
    unsigned long hash = 5381;
    const unsigned char *ptr = (unsigned char *)key;

    for (size_t i = 0; i < k_size; i++) {
        hash = ((hash << 5) + hash) + (*(ptr + i));
    }
    return (hash % size);
}

// algoritmo djb2 for strings
size_t hm_hash_s(const void *key, const size_t k_size, const size_t size) {
    unsigned long hash = 5381;
    const unsigned char *ptr = (unsigned char *)key;

    for (size_t i = 0; i < k_size; i++) {
        if (ptr[i] == '\0')
            break;
        hash = ((hash << 5) + hash) + (*(ptr + i));
    }
    return (hash % size);
}

int hm_resize(hm_map_t *const hmap) {
    // save old hmap
    size_t old_size = hmap->size;
    hm_entry_t *old_entries = hmap->entries;

    // create the new structure
    hmap->size = old_size * 2;
    hmap->entries = malloc(hmap->size * sizeof(hm_entry_t));

    if (hmap->entries == NULL) {
        fprintf(stderr, "Failed to resize\n");
        hmap->entries = old_entries;
        hmap->size = hmap->size / 2;
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < hmap->size; i++) {
        hmap->entries[i].key = malloc(hmap->key_size);
        hmap->entries[i].value = malloc(hmap->value_size);
        hmap->entries[i].tombstone = EMPTY;
    }

    // copy the entries to the new hashmap
    hmap->count = 0;
    for (size_t i = 0; i < old_size; i++) {
        if (old_entries[i].tombstone == USED) { 
            hm_put(hmap, old_entries[i].key, old_entries[i].value);
        }
        free(old_entries[i].key);
        free(old_entries[i].value);
    }

    free(old_entries);

    return EXIT_SUCCESS;
}

int hm_free(hm_map_t *hmap) {
    for (size_t i = 0; i < hmap->size; i++) {
        free(hmap->entries[i].key);
        free(hmap->entries[i].value);
    }

    free(hmap->entries);
    hmap->count = 0;
    hmap->size = 0;

    return EXIT_SUCCESS;
}
