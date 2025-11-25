#include <stdio.h>

int main()
{
    int p, n, count;
    float r, Si;

    count = 1;
    while (count <= 3)
    {
        printf("Enter P (principal), N (time), and R (rate):\n");
        scanf("%d %d %f", &p, &n, &r);

        Si = (p * n * r) / 100;  // Formula for Simple Interest

        printf("Simple Interest = %.2f\n", Si);

        count = count + 1;
    }
    return 0;
}
