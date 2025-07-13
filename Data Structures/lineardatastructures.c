
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DAY 1: SINGLY LINKED LIST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Node structure for the singly linked list
struct SLL_Node {
    int data;
    struct SLL_Node* next;
};

// Function to create a new node
struct SLL_Node* createSLLNode(int data) {
    struct SLL_Node* newNode = (struct SLL_Node*)malloc(sizeof(struct SLL_Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the list
void insertAtBeginningSLL(struct SLL_Node** head, int data) {
    struct SLL_Node* newNode = createSLLNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Function to insert a node at the end of the list
void insertAtEndSLL(struct SLL_Node** head, int data) {
    struct SLL_Node* newNode = createSLLNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct SLL_Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Function to delete a node by its key (value)
void deleteByKeySLL(struct SLL_Node** head, int key) {
    struct SLL_Node *temp = *head, *prev = NULL;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;
    free(temp);
}

// Function to print the linked list
void printSLL(struct SLL_Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Function to free the entire linked list to prevent memory leaks
void freeSLL(struct SLL_Node** head) {
    struct SLL_Node* current = *head;
    struct SLL_Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DAY 2: DOUBLY LINKED LIST ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Node structure for the doubly linked list
struct DLL_Node {
    int data;
    struct DLL_Node* next;
    struct DLL_Node* prev;
};

// Function to create a new DLL node
struct DLL_Node* createDLLNode(int data) {
    struct DLL_Node* newNode = (struct DLL_Node*)malloc(sizeof(struct DLL_Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert at the beginning of a DLL
void insertAtBeginningDLL(struct DLL_Node** head, int data) {
    struct DLL_Node* newNode = createDLLNode(data);
    newNode->next = *head;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Function to print a DLL
void printDLL(struct DLL_Node* node) {
    struct DLL_Node* last;
    printf("Traversal in forward direction: \n");
    while (node != NULL) {
        printf("%d <-> ", node->data);
        last = node;
        node = node->next;
    }
    printf("NULL\n");
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~ DAY 2: CIRCULAR SINGLY LINKED LIST ~~~~~~~~~~~~~~~~~~~~~~~~~

// Using the same SLL_Node structure

// Function to insert at the beginning of a CSLL
void insertAtBeginningCSLL(struct SLL_Node** head, int data) {
    struct SLL_Node* newNode = createSLLNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head; // Points to itself
        return;
    }
    struct SLL_Node* last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    newNode->next = *head;
    last->next = newNode;
    *head = newNode;
}

// Function to print a CSLL
void printCSLL(struct SLL_Node* head) {
    if (head == NULL) return;
    struct SLL_Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(head)\n");
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DAY 3: STACK IMPLEMENTATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ----- Stack using Dynamic Array -----
#define STACK_ARRAY_CAPACITY 100
struct ArrayStack {
    int top;
    unsigned capacity;
    int* array;
};

struct ArrayStack* createArrayStack() {
    struct ArrayStack* stack = (struct ArrayStack*)malloc(sizeof(struct ArrayStack));
    stack->capacity = STACK_ARRAY_CAPACITY;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isArrayStackFull(struct ArrayStack* stack) {
    return stack->top == stack->capacity - 1;
}

int isArrayStackEmpty(struct ArrayStack* stack) {
    return stack->top == -1;
}

void pushArray(struct ArrayStack* stack, int item) {
    if (isArrayStackFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

int popArray(struct ArrayStack* stack) {
    if (isArrayStackEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1; // Return an indicator of error
    }
    return stack->array[stack->top--];
}

int peekArray(struct ArrayStack* stack) {
    if (isArrayStackEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

// ----- Stack using Linked List -----
// We can reuse the SLL_Node structure. The head will be the top.

void pushLL(struct SLL_Node** top, int data) {
    // Same as insert at beginning for SLL
    insertAtBeginningSLL(top, data);
    printf("%d pushed to stack\n", data);
}

int popLL(struct SLL_Node** top) {
    if (*top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }
    struct SLL_Node* temp = *top;
    *top = (*top)->next;
    int popped = temp->data;
    free(temp);
    return popped;
}

int peekLL(struct SLL_Node* top) {
    if (top == NULL) return -1;
    return top->data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DAY 4: QUEUE IMPLEMENTATION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ----- Queue using Dynamic Array (with wrap-around) -----
struct ArrayQueue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct ArrayQueue* createArrayQueue(unsigned capacity) {
    struct ArrayQueue* queue = (struct ArrayQueue*)malloc(sizeof(struct ArrayQueue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1; // Important for wrap-around
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isArrayQueueFull(struct ArrayQueue* queue) {
    return (queue->size == queue->capacity);
}

int isArrayQueueEmpty(struct ArrayQueue* queue) {
    return (queue->size == 0);
}

void enqueueArray(struct ArrayQueue* queue, int item) {
    if (isArrayQueueFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    printf("%d enqueued to queue\n", item);
}

int dequeueArray(struct ArrayQueue* queue) {
    if (isArrayQueueEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// ----- Queue using Linked List -----
// We can reuse the SLL_Node structure. We need front and rear pointers.
struct LLQueue {
    struct SLL_Node *front, *rear;
};

struct LLQueue* createLLQueue() {
    struct LLQueue* q = (struct LLQueue*)malloc(sizeof(struct LLQueue));
    q->front = q->rear = NULL;
    return q;
}

void enqueueLL(struct LLQueue* q, int data) {
    struct SLL_Node* newNode = createSLLNode(data);
    printf("%d enqueued to queue\n", data);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = newNode;
    q->rear = newNode;
}

int dequeueLL(struct LLQueue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    struct SLL_Node* temp = q->front;
    int data = temp->data;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return data;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DAY 5: HASH TABLE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define HASH_TABLE_SIZE 10

// Hash Node is same as SLL Node, but let's rename for clarity
typedef struct SLL_Node HashNode;
HashNode* hashTable[HASH_TABLE_SIZE];

// Hash function to map values to key
int hashCode(int key) {
    return key % HASH_TABLE_SIZE;
}

// Function to insert a key into the hash table
void insertHash(int key) {
    int hashIndex = hashCode(key);
    // Use insert at beginning for efficiency
    insertAtBeginningSLL(&hashTable[hashIndex], key);
}

// Function to search for a key in the hash table
HashNode* searchHash(int key) {
    int hashIndex = hashCode(key);
    HashNode* current = hashTable[hashIndex];
    while (current != NULL) {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Not found
}

void printHashTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        printSLL(hashTable[i]);
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN DRIVER FUNCTION ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    printf("---------- DAY 1: Singly Linked List ----------\n");
    struct SLL_Node* sll_head = NULL;
    insertAtEndSLL(&sll_head, 10);
    insertAtBeginningSLL(&sll_head, 20);
    insertAtEndSLL(&sll_head, 30);
    insertAtBeginningSLL(&sll_head, 40);
    printf("Created SLL: ");
    printSLL(sll_head);
    deleteByKeySLL(&sll_head, 20);
    printf("SLL after deleting 20: ");
    printSLL(sll_head);
    freeSLL(&sll_head);
    printf("\n");

    printf("---------- DAY 2: Doubly & Circular Linked List ----------\n");
    struct DLL_Node* dll_head = NULL;
    insertAtBeginningDLL(&dll_head, 5);
    insertAtBeginningDLL(&dll_head, 15);
    printDLL(dll_head);

    struct SLL_Node* csll_head = NULL;
    insertAtBeginningCSLL(&csll_head, 100);
    insertAtBeginningCSLL(&csll_head, 200);
    insertAtBeginningCSLL(&csll_head, 300);
    printf("Created CSLL: ");
    printCSLL(csll_head);
    printf("\n");

    printf("---------- DAY 3: Stack ----------\n");
    printf("--- Array Stack ---\n");
    struct ArrayStack* arrayStack = createArrayStack();
    pushArray(arrayStack, 10);
    pushArray(arrayStack, 20);
    printf("%d popped from stack\n", popArray(arrayStack));
    printf("Top element is %d\n", peekArray(arrayStack));

    printf("--- Linked List Stack ---\n");
    struct SLL_Node* ll_stack_top = NULL;
    pushLL(&ll_stack_top, 15);
    pushLL(&ll_stack_top, 25);
    printf("%d popped from stack\n", popLL(&ll_stack_top));
    printf("Top element is %d\n", peekLL(ll_stack_top));
    printf("\n");

    printf("---------- DAY 4: Queue ----------\n");
    printf("--- Array Queue ---\n");
    struct ArrayQueue* arrayQueue = createArrayQueue(5);
    enqueueArray(arrayQueue, 10);
    enqueueArray(arrayQueue, 20);
    enqueueArray(arrayQueue, 30);
    printf("%d dequeued from queue\n", dequeueArray(arrayQueue));

    printf("--- Linked List Queue ---\n");
    struct LLQueue* llQueue = createLLQueue();
    enqueueLL(llQueue, 50);
    enqueueLL(llQueue, 60);
    printf("%d dequeued from queue\n", dequeueLL(llQueue));
    printf("\n");

    printf("---------- DAY 5: Hash Table ----------\n");
    // Initialize hash table buckets to NULL
    for(int i=0; i<HASH_TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
    insertHash(12); // bucket 2
    insertHash(22); // bucket 2
    insertHash(25); // bucket 5
    insertHash(35); // bucket 5
    insertHash(5);  // bucket 5
    printHashTable();
    int key_to_search = 25;
    if (searchHash(key_to_search)) {
        printf("Key %d found in hash table.\n", key_to_search);
    } else {
        printf("Key %d not found.\n", key_to_search);
    }

    return 0;
}
