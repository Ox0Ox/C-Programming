#include<stdio.h>;
#include<conio.h>;  
int add(int a, int b)
{
    return a + b;
}
int mul(int a, int b)
{
    return a * b;
}
int call(int a, int b, int (*f)(int, int))
{
    return f(a, b);
}

// even odd using callback
int even(int a)
{
    return a % 2 == 0;
}
int odd(int a)
{
    return a % 2 != 0;
}
int check(int a, int (*f)(int))
{
    return f(a);
}

// largest and smallest using callback
int largest(int a, int b)
{
    return a > b ? a : b;
}
int smallest(int a, int b)
{
    return a < b ? a : b;
}

int find(int a, int b[]){
    int i;
    int n = sizeof(b)/sizeof(*b);
    for(i=0; i<n; i++){
        if(b[i] == a){
            return i;
        }
    }
}
int main()
{
    printf("%d\n", call(5, 6, add));
    printf("%d\n", call(5, 6, mul));
    printf("%d\n", check(5, even));
    printf("%d\n", check(5, odd));
    printf("%d\n", largest(5, 6));
    printf("%d\n", smallest(5, 6));
    int a = 5;
    int b[] = {1, 2, 3, 4, 5};
    printf("%d\n", find(a, b));
}