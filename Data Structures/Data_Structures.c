#include <stdio.h>
#include <stdlib.h> // For exit() in case of errors, and INT_MIN
#include <limits.h> // For INT_MIN

//-----------------------------------------------------------------------------
// SECTION 1: STACK IMPLEMENTATION (Array-based)
//-----------------------------------------------------------------------------

// Define the maximum size of the stack
#define STACK_MAX_SIZE 5

// Structure to represent a stack
struct Stack {
    int items[STACK_MAX_SIZE]; // Array to store stack elements
    int top;                   // Index of the top element of the stack
};

// Function to initialize an empty stack
// Takes a pointer to the Stack structure as input.
void initStack(struct Stack* s) {
    // Set 'top' to -1, indicating that the stack is initially empty.
    // In an array-based stack, 'top' points to the last inserted element.
    // -1 means no elements are present.
    s->top = -1;
    printf("Stack initialized.\n");
}

// Function to check if the stack is full
// Takes a pointer to the Stack structure as input.
// Returns 1 (true) if full, 0 (false) otherwise.
int stack_isFull(struct Stack* s) {
    // The stack is full if 'top' has reached the last valid index of the array.
    // Array indices are 0 to STACK_MAX_SIZE - 1.
    return s->top == STACK_MAX_SIZE - 1;
}

// Function to check if the stack is empty
// Takes a pointer to the Stack structure as input.
// Returns 1 (true) if empty, 0 (false) otherwise.
int stack_isEmpty(struct Stack* s) {
    // The stack is empty if 'top' is -1.
    return s->top == -1;
}

// Function to add (push) an element onto the stack
// Takes a pointer to the Stack structure and the item to be pushed.
void push(struct Stack* s, int item) {
    // Check for stack overflow condition.
    if (stack_isFull(s)) {
        printf("Stack Overflow! Cannot push item %d.\n", item);
        return; // Exit the function if the stack is full.
    }
    // Increment 'top' to point to the next available position.
    s->top++;
    // Add the item at the new 'top' position.
    s->items[s->top] = item;
    printf("Pushed %d onto the stack.\n", item);
}

// Function to remove (pop) an element from the stack
// Takes a pointer to the Stack structure.
// Returns the popped element. If the stack is empty, prints an error and returns INT_MIN.
int pop(struct Stack* s) {
    // Check for stack underflow condition.
    if (stack_isEmpty(s)) {
        printf("Stack Underflow! Cannot pop from an empty stack.\n");
        return INT_MIN; // Return a sentinel value indicating error.
    }
    // Get the item at the current 'top'.
    int poppedItem = s->items[s->top];
    // Decrement 'top' to remove the element logically.
    s->top--;
    printf("Popped %d from the stack.\n", poppedItem);
    return poppedItem; // Return the popped item.
}

// Function to get the top element of the stack without removing it (peek)
// Takes a pointer to the Stack structure.
// Returns the top element. If the stack is empty, prints an error and returns INT_MIN.
int stack_peek(struct Stack* s) {
    // Check if the stack is empty.
    if (stack_isEmpty(s)) {
        printf("Stack is empty! Cannot peek.\n");
        return INT_MIN; // Return a sentinel value indicating error.
    }
    // Return the item at the current 'top'.
    return s->items[s->top];
}

// Function to display the elements of the stack
// Takes a pointer to the Stack structure.
void display_stack(struct Stack* s) {
    if (stack_isEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    // Iterate from 'top' down to 0 to print elements.
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}


//-----------------------------------------------------------------------------
// SECTION 2: QUEUE IMPLEMENTATION (Array-based Circular Queue)
//-----------------------------------------------------------------------------

// Define the maximum size of the queue
#define QUEUE_MAX_SIZE 5

// Structure to represent a queue
struct Queue {
    int items[QUEUE_MAX_SIZE]; // Array to store queue elements
    int front;                 // Index of the front element
    int rear;                  // Index of the rear element (where new elements are added)
    int currentSize;           // Current number of elements in the queue
};

// Function to initialize an empty queue
// Takes a pointer to the Queue structure as input.
void initQueue(struct Queue* q) {
    // 'front' is the index from where elements are dequeued.
    // 'rear' is the index where new elements are enqueued.
    // In this circular queue implementation:
    // - 'front' points to the first element.
    // - 'rear' points to the next available slot for insertion.
    q->front = 0;
    q->rear = 0; // Or -1, depending on convention. Here, rear points to next empty slot.
    q->currentSize = 0; // Queue is initially empty.
    printf("Queue initialized.\n");
}

// Function to check if the queue is full
// Takes a pointer to the Queue structure.
// Returns 1 (true) if full, 0 (false) otherwise.
int queue_isFull(struct Queue* q) {
    // The queue is full if its current size has reached the maximum capacity.
    return q->currentSize == QUEUE_MAX_SIZE;
}

// Function to check if the queue is empty
// Takes a pointer to the Queue structure.
// Returns 1 (true) if empty, 0 (false) otherwise.
int queue_isEmpty(struct Queue* q) {
    // The queue is empty if its current size is 0.
    return q->currentSize == 0;
}

// Function to add (enqueue) an element to the rear of the queue
// Takes a pointer to the Queue structure and the item to be enqueued.
void enqueue(struct Queue* q, int item) {
    // Check for queue full condition.
    if (queue_isFull(q)) {
        printf("Queue Full! Cannot enqueue item %d.\n", item);
        return; // Exit if the queue is full.
    }
    // Add the item at the 'rear' position.
    q->items[q->rear] = item;
    // Move 'rear' to the next position in a circular manner.
    // (q->rear + 1) % QUEUE_MAX_SIZE ensures wrap-around.
    q->rear = (q->rear + 1) % QUEUE_MAX_SIZE;
    // Increment the current size of the queue.
    q->currentSize++;
    printf("Enqueued %d into the queue.\n", item);
}

// Function to remove (dequeue) an element from the front of the queue
// Takes a pointer to the Queue structure.
// Returns the dequeued element. If empty, prints an error and returns INT_MIN.
int dequeue(struct Queue* q) {
    // Check for queue empty condition.
    if (queue_isEmpty(q)) {
        printf("Queue Empty! Cannot dequeue.\n");
        return INT_MIN; // Return a sentinel value indicating error.
    }
    // Get the item from the 'front' of the queue.
    int dequeuedItem = q->items[q->front];
    // Move 'front' to the next position in a circular manner.
    q->front = (q->front + 1) % QUEUE_MAX_SIZE;
    // Decrement the current size of the queue.
    q->currentSize--;
    printf("Dequeued %d from the queue.\n", dequeuedItem);
    return dequeuedItem; // Return the dequeued item.
}

// Function to get the front element of the queue without removing it
// Takes a pointer to the Queue structure.
// Returns the front element. If empty, prints an error and returns INT_MIN.
int queue_front_element(struct Queue* q) {
    // Check if the queue is empty.
    if (queue_isEmpty(q)) {
        printf("Queue is empty! Cannot get front element.\n");
        return INT_MIN; // Return a sentinel value indicating error.
    }
    // Return the item at the 'front' position.
    return q->items[q->front];
}

// Function to get the rear element of the queue without removing it
// Takes a pointer to the Queue structure.
// Returns the rear element. If empty, prints an error and returns INT_MIN.
// Note: 'rear' in this implementation points to the *next available slot*.
// So, the actual last element is at (q->rear - 1 + QUEUE_MAX_SIZE) % QUEUE_MAX_SIZE.
int queue_rear_element(struct Queue* q) {
    // Check if the queue is empty.
    if (queue_isEmpty(q)) {
        printf("Queue is empty! Cannot get rear element.\n");
        return INT_MIN; // Return a sentinel value indicating error.
    }
    // Calculate the index of the actual last element.
    // (q->rear - 1) might be -1 if rear is 0. Adding QUEUE_MAX_SIZE handles negative results
    // before the modulo operation, ensuring a correct positive index.
    int rearIdx = (q->rear - 1 + QUEUE_MAX_SIZE) % QUEUE_MAX_SIZE;
    return q->items[rearIdx];
}

// Function to display the elements of the queue
// Takes a pointer to the Queue structure.
void display_queue(struct Queue* q) {
    if (queue_isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements (front to rear): ");
    int i;
    int count;
    // Iterate from 'front' for 'currentSize' number of elements, handling wrap-around.
    for (count = 0, i = q->front; count < q->currentSize; count++) {
        printf("%d ", q->items[i]);
        i = (i + 1) % QUEUE_MAX_SIZE; // Move to next element circularly
    }
    printf("\n");
}


//-----------------------------------------------------------------------------
// SECTION 3: MAIN FUNCTION (Demonstration)
//-----------------------------------------------------------------------------
int main() {
    printf("--- Stack Demonstration ---\n");
    struct Stack myStack; // Declare a stack variable
    initStack(&myStack);  // Initialize the stack

    // Push operations
    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);
    display_stack(&myStack); // Expected: 30 20 10

    printf("Top element (peek): %d\n", stack_peek(&myStack)); // Expected: 30

    // Pop operations
    pop(&myStack); // Pops 30
    display_stack(&myStack); // Expected: 20 10
    pop(&myStack); // Pops 20
    display_stack(&myStack); // Expected: 10

    // Test stack full
    printf("\nTesting Stack Full condition (Max Size: %d):\n", STACK_MAX_SIZE);
    push(&myStack, 40); // Stack: 40 10
    push(&myStack, 50); // Stack: 50 40 10
    push(&myStack, 60); // Stack: 60 50 40 10
    push(&myStack, 70); // Stack: 70 60 50 40 10 (Now full)
    display_stack(&myStack);
    push(&myStack, 80); // Should print Stack Overflow

    // Test stack empty
    printf("\nTesting Stack Empty condition:\n");
    while (!stack_isEmpty(&myStack)) {
        pop(&myStack);
    }
    display_stack(&myStack); // Should print Stack is empty
    pop(&myStack);           // Should print Stack Underflow
    printf("Peek on empty stack: %d (INT_MIN if error)\n", stack_peek(&myStack));


    printf("\n\n--- Queue Demonstration ---\n");
    struct Queue myQueue; // Declare a queue variable
    initQueue(&myQueue);  // Initialize the queue

    // Enqueue operations
    enqueue(&myQueue, 100);
    enqueue(&myQueue, 200);
    enqueue(&myQueue, 300);
    display_queue(&myQueue); // Expected: 100 200 300

    printf("Front element: %d\n", queue_front_element(&myQueue)); // Expected: 100
    printf("Rear element: %d\n", queue_rear_element(&myQueue));   // Expected: 300

    // Dequeue operations
    dequeue(&myQueue); // Dequeues 100
    display_queue(&myQueue); // Expected: 200 300
    printf("Front element after dequeue: %d\n", queue_front_element(&myQueue)); // Expected: 200

    enqueue(&myQueue, 400); // Queue: 200 300 400
    display_queue(&myQueue);

    // Test queue full
    printf("\nTesting Queue Full condition (Max Size: %d):\n", QUEUE_MAX_SIZE);
    enqueue(&myQueue, 500); // Queue: 200 300 400 500
    enqueue(&myQueue, 600); // Queue: 200 300 400 500 600 (Now full)
    display_queue(&myQueue);
    enqueue(&myQueue, 700); // Should print Queue Full

    // Test circular behavior
    printf("\nTesting Queue circular behavior:\n");
    dequeue(&myQueue); // Dequeues 200. Front moves.
    dequeue(&myQueue); // Dequeues 300. Front moves.
    display_queue(&myQueue); // Expected: 400 500 600
    enqueue(&myQueue, 800); // Enqueues 800 at the wrapped-around rear.
    display_queue(&myQueue); // Expected: 400 500 600 800
    enqueue(&myQueue, 900); // Enqueues 900.
    display_queue(&myQueue); // Expected: 400 500 600 800 900 (Full again)

    // Test queue empty
    printf("\nTesting Queue Empty condition:\n");
    while (!queue_isEmpty(&myQueue)) {
        dequeue(&myQueue);
    }
    display_queue(&myQueue); // Should print Queue is empty
    dequeue(&myQueue);       // Should print Queue Empty
    printf("Front on empty queue: %d (INT_MIN if error)\n", queue_front_element(&myQueue));
    printf("Rear on empty queue: %d (INT_MIN if error)\n", queue_rear_element(&myQueue));

    return 0; // Indicate successful execution
}
