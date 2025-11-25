#include <stdio.h>

int main() {
    int x, y, z;
    printf("Enter the dimensions of 3D array (x y z): ");
    scanf("%d %d %d", &x, &y, &z);

    int arr[x][y][z];

    // Taking input
    printf("Enter elements of 3D array:\n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                printf("arr[%d][%d][%d] = ", i, j, k);
                scanf("%d", &arr[i][j][k]);
            }
        }
    }

    // Displaying output
    printf("\n3D Array elements are:\n");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                printf("%d ", arr[i][j][k]);
            }
            printf("\t"); // separate layers
        }
        printf("\n");
    }

    return 0;
}
