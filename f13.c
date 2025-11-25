#include <stdio.h>
int main(){
    int arr [10],i,n,min,max,sum=0;
    float avg;
    printf("Enter number of elements (max 10): ");
    scanf("%d",&n);
    printf("Enter %d elements:\n",n);   
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    min = max - arr[0];
    for(i=0;i<n;i++){
        sum = sum + arr[i];
        if(arr[i]<min){
            min = arr[i];
        }
        if(arr[i]>max){
            max = arr[i];
        }
    }
    avg = (float)sum/n;
    printf("Minimum: %d\n",min);
    printf("Maximum: %d\n",max);        
    printf("Sum: %d\n",sum);
    printf("Average: %.2f\n",avg);
    return 0;
}