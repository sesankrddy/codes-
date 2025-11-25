#include <stdio.h>

int main() {
    int n = 8;       // Number of terms
    int first = 0, second = 1, next;

    printf("Fibonacci Series (8 terms): ");

    for (int i = 0; i < n; i++) {
        if (i <= 1)
            next = i;
        else {
            next = first + second;
            first = second;
            second = next;
        }
        printf("%d ", next);
    }

    return 0;
}
