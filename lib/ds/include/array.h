#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stdio.h>

/*
 * [Header][array][1][2]....[count]
 *    ^       ^
 *
 * To use the dynamic array lib:
 * 1. Include this file
 * 2. Declare the array: datatype *var = NULL
 * 3. Use the functions
 *
 * Functions:
 * ------------
 *  1. arr_push(arr, x)
 *  Inserts an element at the end of the array or initialize it if it is NULL
 *
 *  2. arr_pop(arry, value)
 *  Remove the last element of the array and return it
 *
 *  3. arr_len(arr)
 *  Return the length of the array
 *
 *  4. arr_size(arr)
 *  Return the capacity of the array, when the capacity is exceded it will
 *  resize
 *
 *  5. arr_free(arr)
 *  Free the memory pointed by the array
 *
 *  TODO: Add needed functions
 *  Init with a size passed as parameter
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
                (Header *)malloc(sizeof(*(arr)) * ARR_INIT_SIZE +           \
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

#define arr_pop(arr, value)                                                 \
    do {                                                                    \
        if ((arr) != NULL && ((Header *)(arr) - 1)->count > 0) {            \
            ((Header *)(arr) - 1)->count--;                                 \
            (value) = (arr)[((Header *)(arr) - 1)->count];                  \
        } else {                                                            \
            (value) = 0;                                                    \
        }                                                                   \
    } while (0);

#define arr_len(arr)    (((arr) != NULL) ? (((Header *)(arr) - 1)->count) : 0)
#define arr_size(arr)   (((arr) != NULL) ? (((Header *)(arr) - 1)->size) : 0)

#define arr_free(arr)                                                       \
do {                                                                        \
    if ((arr) != NULL) {                                                    \
        free((Header *)(arr) - 1);                                          \
        (arr) = NULL;                                                       \
    }                                                                       \
} while (0);

#endif /* ARRAY_H */
