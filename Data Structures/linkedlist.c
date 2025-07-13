// #include <stdio.h>
// #include <stdlib.h>  // Required for malloc and free functions

// typedef struct node {
//     int info;
//     struct node *link;
// } N;

// // Function to insert a node at the beginning of the list
// N* insert(N *head, int ele) {
//     N *newptr = (N*)malloc(sizeof(N));
//     if (newptr == NULL) {
//         printf("Memory allocation failed\n");
//         return head;
//     }
//     newptr->info = ele;
//     newptr->link = head;
//     head = newptr;
//     return head;
// }

// // Function to delete the first node from the list
// N* delete(N *head, int *dele) {
//     if (head == NULL) {
//         printf("List is empty. Nothing to delete.\n");
//         return NULL;
//     }
    
//     N *r = head;
//     *dele = head->info;
//     head = head->link;
//     free(r);
//     return head;
// }

// // Function to free the entire list
// N* freelist(N *head) {
//     N *r = head;
//     while (r != NULL) {
//         head = head->link;
//         free(r);
//         r = head;
//     }
//     return NULL;
// }

// // Function to display all elements in the list
// void display(N *head) {
//     if (head == NULL) {
//         printf("List is empty.\n");
//         return;
//     }
    
//     printf("List elements: ");
//     N *temp = head;
//     while (temp != NULL) {
//         printf("%d ", temp->info);
//         temp = temp->link;
//     }
//     printf("\n");
// }

// int main() {
//     N *head = NULL;
//     int ele, choice, dele;
    
//     do {
//         printf("\n 1. Insert\n 2. Display\n 3. Delete\n 4. Exit\n");
//         printf("Enter your choice: ");
//         scanf("%d", &choice);
        
//         switch(choice) {
//             case 1:
//                 printf("Enter the element to be inserted: ");
//                 scanf("%d", &ele);
//                 head = insert(head, ele);
//                 break;
//             case 2:
//                 display(head);
//                 break;
//             case 3:
//                 head = delete(head, &dele);
//                 if (head != NULL || dele) {  // This checks if deletion occurred
//                     printf("Element deleted is %d\n", dele);
//                 }
//                 break;
//             case 4:
//                 head = freelist(head);  // Free memory before exiting
//                 printf("Exiting...\n");
//                 break;
//             default:
//                 printf("Invalid choice. Please try again.\n");
//         }
//     } while (choice != 4);
    
//     return 0;
// }









#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
struct Node* add_top(struct Node* head, int data);
struct Node* add_bottom(struct Node* head, int data);
struct Node* delete_top(struct Node* head);
struct Node* delete_bottom(struct Node* head);
struct Node* search(struct Node* head, int data);
void print_list(struct Node* head);
void free_list(struct Node* head);

// Add node at the top (head) of the list
struct Node* add_top(struct Node* head, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        return head;
    }
    new_node->data = data;
    new_node->next = head;
    return new_node;
}

// Add node at the bottom (tail) of the list
struct Node* add_bottom(struct Node* head, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        return head;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (!head) {
        return new_node;
    }

    struct Node* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

// Delete node from the top (head) of the list
struct Node* delete_top(struct Node* head) {
    if (!head) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

// Delete node from the bottom (tail) of the list
struct Node* delete_bottom(struct Node* head) {
    if (!head) {
        fprintf(stderr, "List is empty\n");
        return NULL;
    }
    if (!head->next) {
        free(head);
        return NULL;
    }

    struct Node* current = head;
    while (current->next->next) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return head;
}

// Search for a node with given data
struct Node* search(struct Node* head, int data) {
    struct Node* current = head;
    while (current) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Print the linked list
void print_list(struct Node* head) {
    struct Node* current = head;
    printf("Linked List: ");
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Free the entire linked list
void free_list(struct Node* head) {
    struct Node* current = head;
    while (current) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;

    // Add nodes
    head = add_top(head, 10);
    head = add_top(head, 20);
    head = add_bottom(head, 30);
    head = add_bottom(head, 40);
    print_list(head); // Output: Linked List: 20 -> 10 -> 30 -> 40 -> NULL

    // Delete from top
    head = delete_top(head);
    print_list(head); // Output: Linked List: 10 -> 30 -> 40 -> NULL

    // Delete from bottom
    head = delete_bottom(head);
    print_list(head); // Output: Linked List: 10 -> 30 -> NULL

    // Search for nodes
    int search_data = 30;
    struct Node* found = search(head, search_data);
    if (found) {
        printf("Found %d in the list\n", search_data); // Output: Found 30
    } else {
        printf("%d not found\n", search_data);
    }

    search_data = 50;
    found = search(head, search_data);
    if (found) {
        printf("Found %d in the list\n", search_data);
    } else {
        printf("%d not found\n", search_data); // Output: 50 not found
    }

    // Free the list
    free_list(head);
    printf("Linked list freed\n");

    return 0;
}