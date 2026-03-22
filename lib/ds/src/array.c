#include <stdlib.h>
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
 * @size:       size of the elements
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
 * @param arr:  arr to free
 * @return:     a NULL pointer
 */
void *_arr_free(void *arr) {
    if (arr != NULL)
        free(arr_get_header(arr));
    return NULL;
}
