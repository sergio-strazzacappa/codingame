#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Receives a char and return a binary representation of it
void to_binary(char c, char binary[]) {
    size_t i = 0;

    while (c > 0) {
        binary[i++] = (c % 2) + '0';
        c /= 2;
    }
    binary[i] = '\0';

    // complete up to 7 bits with zeros
    while (strlen(binary) < 7) {
        binary[i++] = '0';
        binary[i] = '\0';
    }

    // revert the string
    for (size_t i = 0; i < strlen(binary) / 2; i++) {
        char tmp = binary[strlen(binary) - i - 1];
        binary[strlen(binary) - i - 1] = binary[i];
        binary[i] = tmp;
    }
}

void solve(char message[]) {
    char binary_message[1000] = "";
    char binary[8];

    for (int i = 0; i < strlen(message); i++) {
        to_binary(message[i], binary);
        strcat(binary_message, binary);
    }

    char last = '-';
    char encoded_message[1000] = "";
    size_t i = 0;

    for (size_t j = 0; j < strlen(binary_message); j++) {
        char current = binary_message[j];

        if (current == last) {
            encoded_message[i++] = '0';
        } else if (last == '-') { // sentinel marking the start of the seq
            if (current == '0') {
                encoded_message[i++] = '0';
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            } else {
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            }
        } else {
            if (current == '0') {
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            } else {
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
                encoded_message[i++] = ' ';
                encoded_message[i++] = '0';
            }
        }
        last = current;
    }

    encoded_message[i] = '\0';
    printf("%s\n", encoded_message);
}

int main() {
    char message[101];
    scanf("%[^\n]", message);

    solve(message);

    return EXIT_SUCCESS;
}
