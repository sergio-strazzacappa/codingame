#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

void encode(const char message[], char encoded_message[]) {
    size_t offset = 1;
    bool start = false;

    while (strlen(message) > 0) {
        if (start) {
            memmove(encoded_message + offset, encoded_message,
                    strlen(encoded_message) + 1);

            for (size_t i = 0; i < offset; i++)
                encoded_message[i] = message[i];
        } else {
            size_t len = strlen(encoded_message);
            size_t i;
            for (i = 0; i < offset; i++) {
                encoded_message[len + i] = message[i];
            }
            encoded_message[len + i] = '\0';
        }
        message += offset;
        offset++;
        start = !start;
    }
}

// decode iterating begin-end-begin... and append the decoded text from the end
void decode(const char message[], char decoded_message[]) {
    size_t total = 0;
    size_t offset = 1;
    size_t rest = 0;
    bool start = true;
    size_t len = strlen(message);

    // get the total number offsets (increasing iteration)
    while (true) {
        if (total + offset > len) {
            offset--;
            rest = len - total;
            start = !start;
            break;
        }

        start = !start;
        total += offset;
        offset++;
    }

    decoded_message[len] = '\0';
    size_t s = 0;
    size_t e = 0;

    // decode from the last offset to the end of the message
    if (rest > 0) {
        if (start) {
            strncpy(&decoded_message[len - rest], message, rest);
            s += rest;
        } else {
            strncpy(&decoded_message[len - rest], &message[len - rest], rest);
            e += rest;
        }
        start = !start;
    }

    // decode the message from 1 to offset
    while (offset > 0) {
        if (start) {
            strncpy(&decoded_message[len - s - e - offset], &message[s], offset);
            s += offset;
        } else {
            strncpy(&decoded_message[len - s - e - offset], &message[len - e - offset], offset);
            e += offset;
        }

        offset--;
        start = !start;
    }
}

void solve(char message[], int n) {
    char transformed_message[1025] = "";

    if (n < 0) {
        // encode
        for (size_t i = 0; i < abs(n); i++) {
            transformed_message[0] = '\0';
            encode(message, transformed_message);
            size_t len = strlen(transformed_message);
            strncpy(message, transformed_message, len);
            message[len] = '\0';
        }
    } else if (n > 0) {
        // decode
        for (size_t i = 0; i < abs(n); i++) {
            transformed_message[0] = '\0';
            decode(message, transformed_message);
            size_t len = strlen(transformed_message);
            strncpy(message, transformed_message, len);
            message[len] = '\0';
        }
    } else {
        // n cant' be zero
        assert(0);
    }

    printf("%s\n", transformed_message);
}

int main(void) {
    int n;
    scanf("%d", &n);
    fgetc(stdin);

    char message[1025];
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    solve(message, n);

    return EXIT_SUCCESS;
}
