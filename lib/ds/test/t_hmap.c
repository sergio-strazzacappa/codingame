#include <stdio.h>
#include <assert.h>
#include "../include/hmap.h"

int int_cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    hm_map_t map;
    hm_init(&map, sizeof(int), sizeof(int), int_cmp);

    // Insertar 20 elementos (esto disparará varios resizes)
    for (int i = 0; i < 20; i++) {
        int val = i * 10;
        hm_put(&map, &i, &val);
    }

    // Verificar datos
    for (int i = 0; i < 20; i++) {
        int *res = (int*)hm_get(&map, &i);
        assert(res != NULL && *res == i * 10);
    }

    printf("Test pasado: %zu elementos insertados y verificados.\n", map.count);
    
    hm_free(&map);
    return 0;
}
