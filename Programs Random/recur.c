#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
    int reverse(int n) { int rev = 0; while (n != 0) { rev = rev * 10 + n % 10; n /= 10; } return rev; }
    int palindrome(int n) { return n == reverse(n); }
    int palindrome1(char *str) { int len = strlen(str); for (int i = 0; i < len / 2; i++) { if (str[i] != str[len - i - 1]) return 0; } return 1; };
    int prime(int n) { if (n <= 1) return 0; for (int i = 2; i <= sqrt(n); i++) { if (n % i == 0) return 0; } return 1; }
    int armstrong(int n) { int sum = 0, temp = n; while (temp != 0) { sum += pow(temp % 10, 3); temp /= 10; } return sum == n; }
    int fact(int n){return n == 1 ? 1 : n * fact(n-1);}
    
    int main()
    {
        // printf("%d\n", recur(5));        
        printf("%d\n", fact(5));   
        printf("%d\n", armstrong(153));
        printf("%d\n", prime(5));
        printf("%d\n", palindrome(121));
        printf("%d\n", reverse(12345));
        int a = 5;
        int b = 5;

        a = a++;  // post-increment
        b = ++b;  // pre-increment
        printf("%d %d\n", a, b);  // Output: 5 6
        printf("%d %d\n", a++, ++b);  // Output: 5 7

    }
