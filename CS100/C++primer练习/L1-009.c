#include <stdio.h>
int gcd(int a,int b
){
    if(b==0)
        return a;
    return gcd(b, a % b);
}

int main(){
    int n,a,b,fz,fm;
    fz = 0;
    fm = 1;
    scanf("%d", &n);
    for (int i = 0; i < n;i++)
    {
        scanf("%d/%d", &a, &b);
        fz = fz*b+fm*a;
        fm *=b;
        int g = gcd(fz, fm);
        fz /= g;
        fm /= g;
    }
    if(fz&&fz/fm==0)
        printf("%d/%d", fz, fm);
    
    else if(fz%fm==0)
        printf("%d", fz / fm);
    else 
        printf("%d %d/%d", fz / fm, fz %fm, fm);
}