#include <stdio.h>
//function using pass by reference (via pointer)
void updateValue(int *y)
{

    //modifies the original variable using its address
    *y = *y +10;
}
int main()
{
    int x = 50;
    printf("Before update: %d\n", x);

    // passes the address of x
    updateValue(&x);
 //original variable is changed
    printf("After update: %d\n", x);
    return 0;
}