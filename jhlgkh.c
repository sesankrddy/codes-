#include <stdio.h>

int main() {
    int n, i, j;

    // How many rows you want (for your example, enter 3)
    printf("Enter number of rows: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        // (Optional) spaces to make it look like a pyramid
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // Increasing numbers: i to (2*i - 1)
        for (j = i; j <= 2 * i - 1; j++) {
            printf("%d", j);
        }

        // Decreasing numbers: (2*i - 2) down to i
        for (j = 2 * i - 2; j >= i; j--) {
            printf("%d", j);
        }

        printf("\n");
    }

    return 0;
}