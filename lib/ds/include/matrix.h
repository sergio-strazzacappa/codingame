#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *  Functions:
 *  ----------
 *  1. mat_init(mat, r, c, s)
 *      Initialize the matrix r X c with element of size s
 *
 *  2. mat_insert(mat, r, c, e)
 *      Inserts the element e at pos (c, r)
 *
 *  3. mat_get(mat, r, c)
 *      Access the element at pos (c, r)
 *
 *      r-value:
 *      int val = mat_get(mat, 1, 1);
 *
 *      l-value:
 *      mat_get(mat, 1, 1) = 5
 *
 *  4. mat_free(mat)
 *      Free the memory used
 */

typedef struct mat_header_s {
    size_t rows;
    size_t cols;
} mat_header_t;

#define mat_init(mat, r, c, s)                                              \
    do {                                                                    \
        if ((r) <= 0 || (c) <= 0) {                                         \
            fprintf(stderr, "Invalid sizes\n");                             \
            (mat) = NULL;                                                   \
            break;                                                          \
        }                                                                   \
                                                                            \
        size_t init = (r) * (c) * (s) + sizeof(mat_header_t);               \
        mat_header_t *header = (mat_header_t *)calloc(1, init);             \
                                                                            \
        if (header == NULL) {                                               \
            fprintf(stderr, "Failed to initialize the matrix\n");           \
            (mat) = NULL;                                                   \
            break;                                                          \
        }                                                                   \
                                                                            \
        header->rows = (r);                                                 \
        header->cols = (c);                                                 \
        (mat) = (void *)(header + 1);                                       \
    } while (0);

#define mat_insert(mat, r, c, e)                                            \
    do {                                                                    \
        if ((mat) == NULL) {                                                \
            fprintf(stderr, "Matrix is null\n");                            \
            break;                                                          \
        }                                                                   \
                                                                            \
        mat_header_t *h = ((mat_header_t *)(mat) - 1);                      \
                                                                            \
        if ((r) < 0 || (r) >= h->rows || (c) < 0 || (c) >= h->cols) {       \
            fprintf(stderr, "Invalid position\n");                          \
            break;                                                          \
        }                                                                   \
                                                                            \
        size_t index = (r) * h->cols + (c);                                 \
        (mat)[index] = (e);                                                 \
    } while (0);

// [r][c] = (r * cols) + c
#define mat_get(mat, r, c)                                                  \
    ((mat)[(r) * ((mat_header_t *)(mat) - 1)->cols + (c)])                  \

#define mat_free(mat)                                                       \
    do {                                                                    \
        if ((mat) == NULL) {                                                \
            break;                                                          \
        }                                                                   \
                                                                            \
        free(((mat_header_t*)(mat) - 1));                                   \
        (mat) = NULL;                                                       \
    } while (0);

#endif /* MATRIX_H */
