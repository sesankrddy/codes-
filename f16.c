#include <stdio.h>
int main() {
    int a[10][10], b[10][10], sum[10][10];
    int rows, cols, i, j;

    // Input for matrix dimensions
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    // Input validation
    if (rows > 10 || cols > 10 || rows <= 0 || cols <= 0) {
        printf("Invalid matrix size! Please enter values between 1 and 10.\n");
        return 1;
    }

    // Input for first matrix
    printf("Enter elements of first matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Input for second matrix
    printf("Enter elements of second matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &b[i][j]);
        }
    }

    // Calculate sum of matrices
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }

    // Display result
    printf("Sum of the two matrices:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", sum[i][j]);
        }
        printf("\n");
    }

    return 0;
}
