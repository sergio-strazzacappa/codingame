#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../../../lib/ds/include/hmap.h"

#define EXT_MAX_SIZE        10
#define MIME_TYPE_MAX_SIZE  50
#define FNAME_MAX_SIZE      256

void print_hmap(hm_map_t map) {
    fprintf(stderr, "[DEBUG] ---------------\n");
    for (size_t i = 0; i < map.size; i++) {
        if (map.entries[i].tombstone == USED)
            fprintf(stderr, "[DEBUG] %s -> %s at index %zu\n",
                (char *)map.entries[i].key, (char *)map.entries[i].value, i);
    }
    fprintf(stderr, "[DEBUG] ---------------\n");
}

int cmp(const void *a, const void *b) {
    char *s1 = (char *)a;
    char *s2 = (char *)b;

    return strcmp(s1, s2);
}

int solve(hm_map_t map, const char fname[]) {
    char *ext = "";
    char *last_dot = strrchr(fname, '.');

    if (last_dot == NULL) {
        printf("UNKNOWN\n");
        return EXIT_SUCCESS;
    }


    if (strlen(last_dot) > 0) {
        ext = last_dot + 1;
    }

    if (strlen(ext) > 0) {
        // change case to lowercase if needed
        for (int k = 0; ext[k] != '\0'; k++) {
            if (isupper(ext[k]))
                ext[k] += 'a' - 'A';
        }
    }

    if (strlen(ext) == 0) {
        printf("UNKNOWN\n");
    } else {
        void *ptr = hm_get(&map, ext);

        if (!ptr)
            printf("UNKNOWN\n");
        else {
            char *mime = (char *)ptr;
            printf("%s\n", mime);
        }
    }
    return EXIT_SUCCESS;
}

int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    hm_map_t map;
    hm_init(&map, 11, 51, STRING, cmp);

    for (int i = 0; i < n; i++) {
        char ext[11];
        char mt[51];

        scanf("%s%s", ext, mt);
        fgetc(stdin);

        // change case to lowercase if needed
        for (int j = 0; ext[j] != '\0'; j++) {
            if (isupper(ext[j]))
                ext[j] += 'a' - 'A';
        }

        hm_put(&map, ext, mt);
    }

    //print_hmap(map);

    for (int i = 0; i < q; i++) {
        char fname[FNAME_MAX_SIZE + 1];
        scanf("%s", fname);
        fgetc(stdin);

        solve(map, fname);
    }

    return EXIT_SUCCESS;
}
