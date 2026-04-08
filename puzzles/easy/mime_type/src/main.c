#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define EXT_MAX_SIZE        10
#define MIME_TYPE_MAX_SIZE  50
#define MAX_ELEM            10000
#define FNAME_MAX_SIZE      256

typedef struct mime_s {
    char extension[EXT_MAX_SIZE + 1];
    char mime_type[MIME_TYPE_MAX_SIZE + 1];
} mime_t;

/**
 * implementation of binary search to find the extension in the assocation
 * table
 */
int search(mime_t table[], size_t table_size, char ext[]) {
    int low = 0;
    int mid = 0;
    int high = table_size - 1;

    while (low <= high) {
        mid = low + (high - low) / 2;

        if (strcmp(ext, table[mid].extension) > 0)
            low = mid + 1;
        else if (strcmp(ext, table[mid].extension) < 0)
            high = mid - 1;
        else
            return mid;
    }
    return -1;
}

void solve(mime_t table[], size_t table_size, char fname[]) {
    char *ext = "";
    char *last_dot = strrchr(fname, '.');

    if (last_dot == NULL) {
        printf("UNKNOWN\n");
        return;
    }


    if (strlen(last_dot) > 0)
        ext = last_dot + 1;

    if (strlen(ext) > 0) {
        // change case to lowercase if needed
        size_t j = 0;
        while (ext[j] != '\0') {
            ext[j] = tolower(ext[j]);
            j++;
        }
    }

    if (strlen(ext) == 0) {
        printf("UNKNOWN\n");
    } else {
        int index = search(table, table_size, ext);

        if (index == -1)
            printf("UNKNOWN\n");
        else
            printf("%s\n", table[index].mime_type);
    }
}

int cmp(const void *a, const void *b) {
    mime_t *m1 = (mime_t *)(a);
    mime_t *m2 = (mime_t *)(b);

    return strcmp(m1->extension, m2->extension);
}

int main() {
    size_t n, q;
    scanf("%zu%zu", &n, &q);

    mime_t table[MAX_ELEM];
    size_t table_size = 0;

    for (size_t i = 0; i < n; i++) {
        mime_t m;
        scanf("%s%s", m.extension, m.mime_type);
        fgetc(stdin);

        // change case to lowercase if needed
        size_t j = 0;
        while (m.extension[j] != '\0') {
            m.extension[j] = tolower(m.extension[j]);
            j++;
        }
        table[table_size++] = m;
    }


    qsort(table, table_size, sizeof(mime_t), cmp);

    for (size_t i = 0; i < q; i++) {
        char fname[FNAME_MAX_SIZE + 1];
        scanf("%s", fname);
        fgetc(stdin);

        solve(table, table_size, fname);
    }

    return EXIT_SUCCESS;
}
