#include <stdio.h>
#include <stdlib.h>
#include "../include/array.h"

int main() {
    printf("INIT THE TEST\n");

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    printf("Array of Ints\n");

    int *arr_i = NULL;

    for (size_t i = 0; i < 20; i++) {
        arr_push(arr_i, i);
        printf("capacity: %zu\n", arr_cap(arr_i));
    }

    for (size_t i = 0; i < arr_len(arr_i); i++) {
        printf("Element %zu: %d\n", (i + 1), arr_i[i]);
    }

    for (size_t i = 0; i < 5; i++) {
        arr_pop(arr_i);
    }

    for (size_t i = 0; i < arr_len(arr_i); i++) {
        printf("Element %zu: %d\n", (i + 1), arr_i[i]);
    }

    arr_free(arr_i);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    printf("Array of Floats\n");

    float *arr_f = NULL;

    for (size_t i = 0; i < 20; i++) {
        arr_push(arr_f, i / 2.);
        printf("capacity: %zu\n", arr_cap(arr_f));
    }

    for (size_t i = 0; i < 20; i++) {
        printf("Element %zu: %.1f\n", (i + 1), arr_f[i]);
    }

    for (size_t i = 0; i < 5; i++) {
        arr_pop(arr_f);
    }

    for (size_t i = 0; i < arr_len(arr_f); i++) {
        printf("Element %zu: %f\n", (i + 1), arr_f[i]);
    }

    arr_free(arr_f);

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    printf("Array of Structs\n");

    struct s {
        int x;
        float y;
    };

    struct s *arr_s = NULL;

    for (size_t i = 0; i < 20; i++) {
        struct s elem = {i, i / 2.0};
        arr_push(arr_s, elem);
        printf("capacity: %zu\n", arr_cap(arr_s));
    }

    for (size_t i = 0; i < 20; i++) {
        printf("Element %zu: (%d, %.1f)\n", (i + 1), arr_s[i].x, arr_s[i].y);
    }

    for (size_t i = 0; i < 5; i++) {
        arr_pop(arr_s);
    }

    for (size_t i = 0; i < arr_len(arr_s); i++) {
        printf("Element %zu: (%d, %.1f)\n", (i + 1), arr_s[i].x, arr_s[i].y);
    }

    arr_free(arr_s);

    return EXIT_SUCCESS;
}
