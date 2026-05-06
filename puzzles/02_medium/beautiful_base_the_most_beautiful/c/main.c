#include <stdio.h>
#include <math.h>

#define EPSILON 1.0E-15

unsigned long n;

void init();
void solve();

int main() {
    init();
    solve();

    return 0;
}

void init() {
    scanf("%ld", &n);
}

void solve() {
    unsigned long B = -1;

    for (unsigned long b = 2; b <= n;) {
        long double x = logl(n) / logl(b);
        
        if ((x == round(x) || fabsl(x - (int)x) < EPSILON) && x > 1) {
            B = b;
            break;
        }

        b = ceil(pow(n, (double)1 / (int)x));

        if (x < 2)
            break;
    }

    if (B == -1)
        printf("NONE\n");
    else
        printf("%ld\n", B);
}
