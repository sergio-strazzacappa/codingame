#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

/**
 * num is a pointer to a field of the license plate, its the ascii code of any
 * letter or the number in the middle field.
 * mod is 999 for the number [0 - 998]. Substract the offset and calculate the
 * next num in ranage [0 - 998]. It can't be 0, so we apply again the  offset
 * and the new range is [1 - 999]
 */
int solve_num(int *num, size_t n, int mod, int offset) {
    int total = (*num - offset) + n;
    *num= total % mod + offset;

    return total / mod;
}

void solve(int plate[], size_t n) {
    // solved in order of execution
    // [ab, nun, cd]
    // 1. num
    // 2. d
    // 3. c
    // 4. b
    // 5. a
    n = solve_num(&plate[2], n, 999, 1);
    n = solve_num(&plate[4], n, 26, 0);
    n = solve_num(&plate[3], n, 26, 0);
    n = solve_num(&plate[1], n, 26, 0);
    n = solve_num(&plate[0], n, 26, 0);

    assert(n == 0);

    printf("%c%c-%03d-%c%c\n",
        plate[0] + 'A', plate[1] + 'A',
        plate[2],
        plate[3] + 'A', plate[4] + 'A');
}

int main(void) {
    char line[32];

    if (fgets(line, sizeof(line), stdin)) {
        char a, b, c, d;
        int num;
        sscanf(line, "%c%c-%d-%c%c", &a, &b, &num, &c, &d);

        int plate[5] = {a - 'A', b - 'A', num, c - 'A', d - 'A'};

        size_t n;
        scanf("%zu", &n);

        solve(plate, n);
    }

    return EXIT_SUCCESS;
}
