#include<stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: Division by zero\n");
        return 0; // Return 0 or handle error as needed
    }
}

int main() {
    int x = 10, y = 5;
    printf("Add: %d\n", add(x, y));
    printf("Subtract: %d\n", subtract(x, y));
    printf("Multiply: %d\n", multiply(x, y));
    printf("Divide: %d\n", divide(x, y));
    return 0;
}