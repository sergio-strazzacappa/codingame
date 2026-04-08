#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROW_SIZE 1025

void debug(int width, int height, char *text, char **representation, size_t size) {
    fprintf(stderr, "### START DEBUG ###\n");

    fprintf(stderr, "The width is: %d\n", width);
    fprintf(stderr, "The height is: %d\n", height);
    fprintf(stderr, "The text is: %s\n", text);
    fprintf(stderr, "The representation is:\n");

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < size; x++)
            fprintf(stderr, "%c", representation[y][x]);
        fprintf(stderr, "\n");
    }

    fprintf(stderr, "### END DEBUG ###\n\n");
}

void solve(int width, int height, char *text, char **representation) {
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < strlen(text); x++) {
            char c = text[x];

            // if c is lowercase, convert it to uppercase
            if (c >= 'a' && c <= 'z')
                c = toupper(c);

            int base = c - 'A';

            // if c is invalid, change base to ?
            if (c < 'A' || c > 'Z')
                base = 'Z' - 'A' + 1;

            for (size_t k = base * width; k < base * width + width; k++)
                printf("%c", representation[y][k]);
        }
        printf("\n");
    }
}

int main() {
    int width;
    int height;
    char text[257];
    char **representation;
    size_t size;

    scanf("%d%d", &width, &height);
    fgetc(stdin);

    scanf("%[^\n]", text);
    fgetc(stdin);

    representation = (char **)malloc(sizeof(char*) * height);

    for (size_t y = 0; y < height; y++) {
        char row[ROW_SIZE];
        scanf("%[^\n]", row);
        fgetc(stdin);

        if (y == 0)
            size = strlen(row);

        representation[y] = (char *)malloc(sizeof(char) * size);

        for (int x = 0; x < size; x++)
            representation[y][x] = row[x];
    }

    solve(width, height, text, representation);

    for (int y = 0; y < height; y++)
        free(representation[y]);
    free(representation);

    return EXIT_SUCCESS;
}
