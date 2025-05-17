#include <stdio.h>
#include <conio.h>
int main()
{
    int a = 0113;
    printf("%d", a);
    printf("%X\n",a);
    printf("\n");

    // perfect number 
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i < n; i++)
    {
        if (n % i == 0)
        {
            sum += i;
        }
    }
    printf("%d\n", sum);
    if (sum == n)
    {
        printf("Perfect number\n");
    }
    else
    {
        printf("Not a perfect number\n");
    }
    // 1 22 333 4444 55555
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("%d", i);
        }
        printf("\n");
    }

    // 1 12 123 1234 12345
    for (int i = 1; i < 6; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            printf("%d", j);
        }
        printf("\n");
    }

    // hollow square pattern g x g size
    int g;
    printf("Enter the size of the square: ");
    scanf("%d", &g);
    for (int i = 1; i <= g; i++)
    {
        for (int j = 1; j <= g; j++)
        {
            if (i == 1 || i == g || j == 1 || j == g)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    // // triangle classifier bassed on two angles
    // int angle1, angle2;
    // printf("Enter the two angles of the triangle: ");
    // scanf("%d %d", &angle1, &angle2);
    // if (angle1 + angle2 == 90)
    // {
    //     printf("Right angled triangle\n");
    // }
    // else if (angle1 + angle2 > 90)
    // {
    //     printf("Obtuse angled triangle\n");
    // }
    // else
    // {
    //     printf("Acute angled triangle\n");
    // }
    // // triangle classifier bassed on sides
    // int side1, side2, side3;
    // printf("Enter the three sides of the triangle: ");
    // scanf("%d %d %d", &side1, &side2, &side3);
    // if (side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2)
    // {
    //     if (side1 == side2 && side2 == side3)
    //     {
    //         printf("Equilateral triangle\n");
    //     }
    //     else if (side1 == side2 || side2 == side3 || side1 == side3)
    //     {
    //         printf("Isosceles triangle\n");
    //     }
    //     else
    //     {
    //         printf("Scalene triangle\n");
    //     }
    // }
    // else
    // {
    //     printf("Not a triangle\n");
    // }

    // // triangle classifier bassed on two angles using nested switch
    // int a1, a2;
    // printf("Enter the two angles of the triangle: ");
    // scanf("%d %d", &a1, &a2);
    // switch (a1)
    // {
    //     case 90:
    //         switch (a2)
    //         {
    //             case 90:
    //                 printf("Right angled triangle\n");
    //                 break;
    //             default:
    //                 printf("Not a triangle\n");
    //                 break;
    //         }
    //         break;
    //     case 180:
    //         switch (a2)
    //         {
    //             case 90:
    //                 printf("Obtuse angled triangle\n");
    //                 break;
    //             default:
    //                 printf("Not a triangle\n");
    //                 break;
    //         }
    //         break;
    //     default:
    //         printf("Acute angled triangle\n");
    //         break;
    //     }


    // largest and smallest elements of an array of y size
    int y;
    printf("Enter the size of the array: ");
    scanf("%d", &y);
    int arr[y];
    for (int i = 0; i < y; i++)
    {
        printf("Enter element number %d: ", i+1);
        scanf("%d", &arr[i]);
    }
    int largest = arr[0], smallest = arr[0];
    printf("The array is: ");
    for (int i = 0; i < y; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    for (int i = 1; i < y; i++)
    {
        if (arr[i] > largest)
        {
            largest = arr[i];
        }
        if (arr[i] < smallest)
        {
            smallest = arr[i];
        }
    }
    printf("Largest element: %d\n", largest);
    printf("Smallest element: %d\n", smallest);


    // +ve -ve and zero count in array of h size
    int h;
    printf("Enter the size of the array: ");
    scanf("%d", &h);
    int arr1[h];
    for (int i = 0; i < h; i++)
    {
        printf("Enter element number %d: ", i+1);
        scanf("%d", &arr1[i]);
    }
    int positive = 0, negative = 0, zero = 0;
    for (int i = 0; i < h; i++)
    {
        if (arr1[i] > 0)
        {
            positive++;
        }
        else if (arr1[i] < 0)
        {
            negative++;
        }
        else
        {
            zero++;
        }
    }
    printf("Positive numbers: %d\n", positive);
    printf("Negative numbers: %d\n", negative);
    printf("Zeroes: %d\n", zero);

    // square matrix confimer of size l x k
    int l, k;
    printf("Enter the size of the matrix (l x k): ");
    scanf("%d %d", &l, &k);
    if(l == k)
    {
        printf("Square matrix\n");
    }
    else
    {
        printf("Not a square matrix\n");
    }

    // turning matrix by 90 degrees clockwise
    int m[l][k];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("Enter element number %d %d: ", i+1, j+1);
            scanf("%d", &m[i][j]);
        }
    }
    int m1[k][l];
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < k; j++)
        {
            m1[j][l-i-1] = m[i][j];
        }
    }
    printf("The original matrix is:\n");
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("The matrix turned by 90 degrees clockwise is:\n");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < l; j++)
        {
            printf("%d ", m1[i][j]);
        }
        printf("\n");
    }
    printf("This is recursion for adding upto n = 5 whole numbers%d\n", recur(5));
}

int recur(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return n + recur(n - 1);
}