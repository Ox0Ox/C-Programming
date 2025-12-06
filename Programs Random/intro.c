#include<stdio.h>

int main()
{
    int a = 10;
    int b;
    int x;
    int z;
    int n = 1729,rem,sum;
    int i;
    int s = 1;
    int v = 0;
    int t = 1;
    printf("%d\n",10);
    printf("%f\n",10.0);
    printf("%lf\n",10.0);
    printf("%c\n",'A');
    printf("%s\n","hello");
    printf("%p\n",&a);
    printf("%x\n",10);
    printf("%o\n",10);
    // scanf("%d",&b);
    // printf("%d\n",b);
    // if(b>0){
    //     printf("b is positive\n");
    // }
    // else if(b<0){
    //     printf("b is negative\n");
    // }
    for (x = 0; x <= 10; x++){
        printf("%d\n",x);
    }
    // do{
    //     printf("%d\n",z);
    // }
    while(z<10){
        z++;
        printf("%d\n",z);
    }
    while(n>9){
        sum = 0;
        while(n){
            sum += n % 10;
            n /= 10;
        }
        n = sum;
    }
    printf("Digital root of 1729(1+7+2+9 = 19, 1+9 = 10, 1+0 = 1, thus answer is 1) %d\n",n);

    for (i = 1; i<10; i++){
        t = v+s;
        printf("%d, ",t);
        v = s;
        s = t;
    }
    printf("\n");  

    int m [10] = {1,2,3,4,5,6,7,8};
    for (i = 0; i<10; i++){
        printf("%d ",m[i]);
    }
    printf("\n");
    int *pointer = m;
    for (i = 0; i<10; i++){
        printf("element number %d is %d\n",i,*pointer);
        *pointer++;
    }

    char str[] = "BEST";
    int y;
    for(y=0; str[y]; y++){
    printf("%d\n",y);
    printf("%s\n",str);
    printf("%c %c %c %c\n", str[y], *(str+y), *(y+str), y[str]+2);}

    

}