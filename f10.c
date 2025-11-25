#include <stdio.h>
int main()
{
    int n, num, i;
    printf("Enter how many numbers you want to get printed:");
    scanf("%d", &n);
    printf ("Enter %d numbers\n", n);

    for (i=1; i<=n; i++)
    {
        scanf("%d", &num);
        printf("Number %d = %d\n", i, num);
    }
    return 0;

}
