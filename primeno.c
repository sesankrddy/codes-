#include <stdio.h>

int main(){
int num , i , isprime = 1, count = 0;
printf("Enter a positive integer: ");
scanf("%d", &num);
if(num <= 1){
    printf("Not a prime number.\n");
    return 0;

}
printf("factors of %d are: ", num);
for(i = 1; i <= num; i++){
    if(num % i == 0){
        printf("%d ", i);
        count++;
    }
}
if(count == 2){
    printf("\n%d is a prime number.\n", num);
} else {
    printf("\n%d is not a prime number.\n", num);
}
    return 0;
}