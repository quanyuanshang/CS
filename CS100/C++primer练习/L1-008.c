#include <stdio.h>
#include <math.h>
int main()
{
    int a, b;
    int count = 0;
    scanf("%d %d", &a, &b);
    int sum = (a + b) * (b - a + 1) / 2;
    for (int i = a; i <= b; i++)
    {
        printf("%5d", i);
        count++;
        if (count == 5)
        {
            printf("\n");
            count = 0;
        }
    }
    if(count!=0)
        printf("\n");
    printf("Sum = %d", sum);
}