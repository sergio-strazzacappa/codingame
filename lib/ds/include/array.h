#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdio.h>

/*
 * [Header][0][1][2]....[count]
 *    ^     ^
 *
 * Functions:
 * ------------
 *  1. arr_push(arr, x)
 *  2. arr_len(arr)
 *  3. arr_size(arr)
 *  4. arr_free(arr)
 *
 *  TODO: Add needed functions
 */

typedef struct Header {
    size_t count;
    size_t size;
} Header;

#define ARR_INIT_SIZE 256

#define arr_push(arr, x)                                                    \
    do {                                                                    \
        if ((arr) == NULL) {                                                \
            Header *header =                                                \
                (Header *)malloc(sizeof(*arr) * ARR_INIT_SIZE +             \
                    sizeof(Header));                                        \
                                                                            \
            if (header == NULL) {                                           \
                fprintf(stderr, "Failed to initialize the array\n");        \
                (arr) = NULL;                                               \
                break;                                                      \
            }                                                               \
                                                                            \
            header->count = 0;                                              \
            header->size = ARR_INIT_SIZE;                                   \
            (arr) = (void *)(header + 1);                                   \
        }                                                                   \
                                                                            \
        Header *header = (Header *)(arr) - 1;                               \
                                                                            \
        if (header->count >= header->size) {                                \
            header->size *= 2;                                              \
            Header *h =                                                     \
                (Header *)realloc(header, sizeof(*arr) * header->size +     \
                sizeof(Header));                                            \
                                                                            \
            if (h == NULL) {                                                \
                fprintf(stderr, "Failed to reallocate the array\n");        \
                (arr) = NULL;                                               \
                break;                                                      \
            }                                                               \
            header = h;                                                     \
            (arr) = (void *)(header + 1);                                   \
        }                                                                   \
                                                                            \
        (arr)[header->count++] = (x);                                       \
    } while (0);

#define arr_len(arr) ((Header *)(arr) - 1)->count
#define arr_size(arr) ((Header *)(arr) - 1)->size
#define arr_free(arr) free((Header *)(arr) - 1);

#endif /* ARRAY_H */
