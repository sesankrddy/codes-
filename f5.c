#include <stdio.h>

int main() {
    int arr[3][3] = {
        {16, 16, 16},
        {16, 16, 16},
        {16, 16, 16}
    };

    printf("3D Array elements:\n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}
