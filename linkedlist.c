#include <stdio.h>
#include <stdlib.h>  // Required for malloc and free functions

typedef struct node {
    int info;
    struct node *link;
} N;

// Function to insert a node at the beginning of the list
N* insert(N *head, int ele) {
    N *newptr = (N*)malloc(sizeof(N));
    if (newptr == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }
    newptr->info = ele;
    newptr->link = head;
    head = newptr;
    return head;
}

// Function to delete the first node from the list
N* delete(N *head, int *dele) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    
    N *r = head;
    *dele = head->info;
    head = head->link;
    free(r);
    return head;
}

// Function to free the entire list
N* freelist(N *head) {
    N *r = head;
    while (r != NULL) {
        head = head->link;
        free(r);
        r = head;
    }
    return NULL;
}

// Function to display all elements in the list
void display(N *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    printf("List elements: ");
    N *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->link;
    }
    printf("\n");
}

int main() {
    N *head = NULL;
    int ele, choice, dele;
    
    do {
        printf("\n 1. Insert\n 2. Display\n 3. Delete\n 4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter the element to be inserted: ");
                scanf("%d", &ele);
                head = insert(head, ele);
                break;
            case 2:
                display(head);
                break;
            case 3:
                head = delete(head, &dele);
                if (head != NULL || dele) {  // This checks if deletion occurred
                    printf("Element deleted is %d\n", dele);
                }
                break;
            case 4:
                head = freelist(head);  // Free memory before exiting
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    
    return 0;
}