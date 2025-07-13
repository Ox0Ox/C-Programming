### 108. Dynamic Array of Structures (6.0 Marks) [Jan–June 2024, Page 100]
**Question**: Write a C program to create a dynamic array of `Student` structures and read/display their data.
```c
struct Student {
    int roll_no;
    char name[50];
};
```

**Answer**:
- **Explanation**: Dynamically allocate memory for `n` `Student` structures using `malloc`. Use `fgets` for safe string input, removing the trailing newline. Free memory after use to prevent leaks.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    int roll_no;
    char name[50];
};
int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);
    struct Student *students = (struct Student*)malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter roll no and name for student %d: ", i + 1);
        scanf("%d", &students[i].roll_no);
        getchar(); // Clear newline
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove trailing newline
    }
    printf("\nStudent Details:\n");
    for (int i = 0; i < n; i++) {
        printf("Student %d: Roll No: %d, Name: %s\n", i + 1, students[i].roll_no, students[i].name);
    }
    free(students);
    return 0;
}

### 109. Bit Manipulation Count Set Bits (5.0 Marks) [Jan–May 2024, Page 91]
**Question**: Write a C function to count the number of set bits (1s) in an integer.
```c
int countSetBits(int num);
```

**Answer**:
- **Explanation**: Use `num & 1` to check the least significant bit and right-shift `num` to process each bit. Alternatively, `num & (num - 1)` clears the rightmost set bit, counting iterations until `num` is 0 (Brian Kernighan’s algorithm is shown here for efficiency).
#include <stdio.h>
int countSetBits(int num) {
    int count = 0;
    while (num) {
        num &= (num - 1); // Clear rightmost set bit
        count++;
    }
    return count;
}
int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Number of set bits: %d\n", countSetBits(num));
    return 0;
}

### 110. Predict Pointer Output (6.0 Marks) [Dec 2023, Page 81]
**Question**: Predict the output:
```c
#include <stdio.h>
int main() {
    int a = 10, b = 20;
    int *p = &a, *q = &b;
    *p = *q;
    printf("%d %d\n", a, b);
    return 0;
}
```

**Answer**:
- **Explanation**: `p` points to `a`, and `q` points to `b`. The assignment `*p = *q` copies the value pointed to by `q` (20) to the location pointed to by `p` (i.e., `a`). Thus, `a` becomes 20, while `b` remains unchanged.
- **Output**: `20 20`