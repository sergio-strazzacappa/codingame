#include "../include/hmap.h"

int int_cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int str_cmp(const void *a, const void *b) {
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;

    return strcmp(s1, s2);
}

int main() {
    // Test hashmap of ints
    printf("---------- BEGIN OF INT TEST ----------\n");
    hm_map_t imap;
    hm_init(&imap, sizeof(int), sizeof(int), INT, int_cmp);

    for (size_t i = 0; i < 20; i++) {
        int val = i * 10;
        printf("Insert value %d. Hashmap size is %zu\n", val, imap.size);
        hm_put(&imap, &i, &val);
    }

    for (size_t i = 0; i < 20; i++) {
        int *res = (int*)hm_get(&imap, &i);
        printf("%d\n", *res);
    }

    hm_free(&imap);

    // Test hashmap of strings
    printf("---------- BEGIN OF STR TEST ----------\n");
    hm_map_t smap;
    hm_init(&smap, sizeof(char *), sizeof(int), STRING, str_cmp);

    char *KEYS[20] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
        "k", "l", "m", "n", "o", "p", "q", "r", "s", "t"
    };

    for (size_t i = 0; i < 20; i++) {
        char *val = KEYS[i];
        printf("Insert value %s. Hashmap size is %zu\n", val, smap.size);
        hm_put(&smap, &val, &i);
    }

    for (size_t i = 0; i < 20; i++) {
        char *search_ptr = KEYS[i];
        int *res = (int *)hm_get(&smap, &search_ptr);
        printf("%d\n", *res);
    }

    hm_free(&smap);

    return EXIT_SUCCESS;
}
