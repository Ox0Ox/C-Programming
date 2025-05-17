#include<stdio.h>
char binary(int n)
{
    if (n == 0)
        return '0';
    else
        return binary(n>>1), putchar('0' + (n & 1));
}

int main()
{   
    int sort(int *a, int n);
    int n = 4;
    binary(n);
    printf("\n");
    int a[] = {19, 12, 31, 14, 45};
    n = sizeof(a)/sizeof(*a);
    sort(a, n);
    for(int i=0; i<n; i++){
        printf("%d ", a[i]);
    }
}

int sort(int *a, int n)
{
    int i, j, temp;
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            if(a[i] > a[j]){
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    // for(i=0; i<n; i++){
    //     printf("%d ", a[i]);
    // }
}
