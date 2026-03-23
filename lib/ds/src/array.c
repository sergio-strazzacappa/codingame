#include <stdlib.h>
#include <string.h>
#include "../include/array.h"

/**
 * @param n:    number of elements
 * @param size: size of each element
 * @return:     a pointer to the array
 */
void *_arr_init(const size_t n, const size_t size) {
    size_t total_size = n * size + sizeof(arr_header_t);
    arr_header_t *h = (arr_header_t *)malloc(total_size);

    if (h == NULL) {
        return NULL;
    }

    h->count = 0;
    h->capacity = n;

    return (void *)(h + 1);
}

/**
 * @param arr:  arr to grow if needed
 * @param size: size of the elements
 * @return:     a pointer to the array
 */
void *_arr_push(void *arr, const size_t size) {
    if (arr == NULL) {
        return _arr_init(INIT_CAPACITY, size);
    }

    arr_header_t *h = arr_get_header(arr);

    if (h->count >= h->capacity) {
        size_t next_capacity = h->capacity * 2;
        size_t total_size = size * next_capacity + sizeof(arr_header_t);
        arr_header_t *new_h = (arr_header_t*)realloc(h, total_size);

        if (new_h == NULL) {
            return arr;
        }

        h = new_h;
        h->capacity = next_capacity;
    }

    return (void *)(h + 1);
}

/**
 * @brief:      copy the src array and returns a pointer to the copy
 * @param src:  arr to copy
 * @param size: size of the elements
 * @return:     a pointer to the copy
 */
void *_arr_cp(void *src, const size_t size) {
    if (src == NULL)
        return NULL;

    arr_header_t* h = arr_get_header(src);
    size_t total_size = arr_cap(src) * size + sizeof(arr_header_t);

    void *dst = (arr_header_t *)malloc(total_size);
    memcpy(dst, h, total_size);

    return (void *)((arr_header_t *)dst + 1);
}

/**
 * @param arr:  arr to free
 * @return:     a NULL pointer
 */
void *_arr_free(void *arr) {
    if (arr != NULL)
        free(arr_get_header(arr));
    return NULL;
}
