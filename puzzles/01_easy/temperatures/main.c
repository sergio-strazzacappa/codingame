#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int closest_temp;

    for (int i = 0; i < n; i++) {
        int temp;
        scanf("%d", &temp);

        if (!i) {
            closest_temp = temp;
        } else {
            if (abs(temp) < abs(closest_temp)) {
                closest_temp = temp;
            } else {
                if (abs(temp) == abs(closest_temp) && temp > 0) {
                    closest_temp = temp;
                }
            }
        }
    }
    printf("%d\n", closest_temp);
    return 0;
}