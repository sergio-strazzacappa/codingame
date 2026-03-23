#ifndef ARRAY_H
#define ARRAY_H

/*
 * [Header][arr][1][2]....[count]
 *    ^       ^
 *
 * To use the dynamic array lib:
 * 1. Include this file
 * 2. Declare the array: datatype *var = NULL
 * 3. Use the functions
 *
 * Functions:
 * ------------
 *
 *  1. arr_init(arr, n)
 *  Creates an array with n elements.
 *  Accepts [] notation.
 *
 *  2. arr_push(arr, x)
 *  Inserts an element at the end of the array or initialize it if it is NULL
 *
 *  3. arr_pop(arr, item)
 *  Remove the last element of the array
 *
 *  4. arr_cp(dst, src)
 *  Make a shallow copy of src into dst
 *
 *  5. arr_len(arr)
 *  Return the length of the array
 *
 *  6. arr_cap(arr)
 *  Return the capacity of the array
 *
 *  7. arr_free(arr)
 *  Free the memory pointed by the array

 *  Internal functions:
 *  -------------------
 *
 *  1. arr_get_header(arr)
 *  Internal macro to access the header
 *
 *  TODO: Add needed functions
 *  insert an element in the middle of the array
 *  remove an element at a specific index
 *  search an element
 *  test if an element exists
 */

#include <stddef.h>

typedef struct {
    size_t count;
    size_t capacity;
} arr_header_t;

#define INIT_CAPACITY 8

#define arr_get_header(arr)                         \
    ((arr_header_t *)(arr) - 1)

#define arr_init(arr, n)                            \
    ((arr) = _arr_init((n), sizeof(*(arr))))

#define arr_push(arr, x)                            \
    do {                                            \
        (arr) = _arr_push((arr), sizeof(*(arr)));   \
        (arr)[arr_get_header(arr)->count++] = (x);  \
    } while (0)

#define arr_pop(arr)                                \
    ((arr) && arr_get_header(arr)->count > 0        \
        ? (--(arr_get_header(arr)->count))          \
        : 0)

#define arr_cp(dst, src)                            \
    (dst) = _arr_cp((src), sizeof(*(src)))

#define arr_len(arr)                                \
    ((arr)                                          \
        ? ((arr_get_header(arr)->count))            \
        : 0)

#define arr_cap(arr)                                \
    ((arr)                                          \
        ? ((arr_get_header(arr)->capacity))         \
        : 0)

#define arr_free(arr)                               \
    (arr) = _arr_free(arr)

void *_arr_init(const size_t n, const size_t size);
void *_arr_push(void *arr, const size_t size);
void *_arr_cp(void *src, const size_t size);
void *_arr_free(void *arr);

#endif /* ARRAY_H */
