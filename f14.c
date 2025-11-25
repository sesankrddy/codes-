#include<stdio.h>

int main(){
    int a, b, temp;
    printf("Enter two integers (a and b): ");
    scanf("%d %d", &a, &b);

    // Swapping using a temporary variable
    temp = a;
    a = b;
    b = temp;

    printf("After swapping:\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    return 0;
}