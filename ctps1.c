#include <stdio.h>

// void function definition 
void hello() {
    printf("sesank\n");
}

// return type function definition
int square(int x) {
    return x * x;
}

int main() {
    // calling void function
    hello();
    
    // calling return type function
    int a = 5;
    int b = square(a);
    
    printf("%d\n", b);
    
    return 0;
}
