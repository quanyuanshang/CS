#include <stdio.h>
#include <math.h>

int main()
{
    int N, temp, max, flag, i, j;
    max = 0;
    scanf("%d", &N);
    flag = 0;
    for (i = 2; i <= sqrt(N); i++)
    {
        temp = N;

        for (j = i; j <= temp; j++)
        {

            if (temp % j == 0)
            {

                temp /= j;
            }
            else
                break;
        }
        if (j - i > max)
        {
            max = j - i;

            flag = i;
        }
    }
    if (max == 0)
        printf("1\n%d", flag);
    else
    {
        printf("%d\n", max);
        for (int i = flag; i < flag + max - 1; i++)
        {
            printf("%d*", i);
        }
        printf("%d", flag + max - 1);
    }
}
