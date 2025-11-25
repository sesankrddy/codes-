#include <stdio.h>
int main(){
    int a = 5 ;
    int b = 10 ;
    int temp;
    printf("Before swapping: a = %d, b = %d\n", a, b);

    temp = a;//store the value of a in temp
    a = b;   //assign the value of b to a
    b = temp;//assign the value stored in temp to b
    printf("After swapping: a = %d, b = %d\n", a, b);
    return 0;
    
}