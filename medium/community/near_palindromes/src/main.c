#include <stdio.h>
#include <string.h>

int solve(char word[]);
int is_palindrome(char word[], int low, int high);

int main() {
    int n;
    scanf("%d", &n);
    fgetc(stdin);

    for (int i = 0; i < n; i++) {
        char word[10001] = "";
        scanf("%[^\n]", word);
        fgetc(stdin);
        printf("%d", solve(word));
    }
    putchar('\n');

    return 0;
}

int solve(char word[]) {
    int low = 0;
    int high = strlen(word) - 1;
 
    while (low < high) {
        if (word[low] != word[high]) {
            if (is_palindrome(word, low + 1, high - 1))
                return 1;
            if (is_palindrome(word, low + 1, high))
                return 1;
            if (is_palindrome(word, low, high - 1))
                return 1;
            return 0;
        }

        low++;
        high--;
    }
    return 1;
}

int is_palindrome(char word[], int low, int high) {
    while (low < high) {
        if (word[low] != word[high])
            return 0;
        low++;
        high--;
    }
    return 1;
}
