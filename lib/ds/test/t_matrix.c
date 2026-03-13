#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"

int main() {
    int *imatrix = NULL;

    mat_init(imatrix, 5, 7, sizeof(int));

    if (imatrix == NULL) {
        return EXIT_SUCCESS;
    }

    mat_header_t *header = (mat_header_t *)imatrix - 1;
    printf("Matrix initilize with rows=%zu, cols=%zu\n", header->rows, header->cols);

    for (size_t y = 0; y < header->rows; y++) {
        for (size_t x = 0; x < header->cols; x++) {
            mat_insert(imatrix, y, x, x * y);
        }
    }

   for (size_t y = 0; y < header->rows; y++) {
        for (size_t x = 0; x < header->cols; x++) {
            printf("%3d", mat_get(imatrix, y, x));
        }
        printf("\n");
    }

    mat_free(imatrix);

    return EXIT_SUCCESS;
}
