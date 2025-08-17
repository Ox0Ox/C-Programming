#include <stdio.h>
#include <stdlib.h>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1. Tree Node Structure Definition
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/**
 * @brief Defines the structure for a node in a binary tree.
 * * Each node contains an integer value (`data`) and two pointers (`left`, `right`)
 * to its left and right children, respectively. If a child does not exist,
 * the corresponding pointer is NULL.
 */
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Function Prototypes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Utility function to create a new node
struct TreeNode* createNode(int data);

// Recursive traversal functions
void inOrderTraversal(struct TreeNode* root);
void preOrderTraversal(struct TreeNode* root);
void postOrderTraversal(struct TreeNode* root);

// Binary Search Tree (BST) specific functions
struct TreeNode* insertNode(struct TreeNode* root, int data);
struct TreeNode* searchNode(struct TreeNode* root, int data);
struct TreeNode* deleteNode(struct TreeNode* root, int data);
struct TreeNode* findMinValueNode(struct TreeNode* node);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Main Function - Demonstration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    printf("--- Binary Tree and Terminology Learning ---\n");
    // Manually creating a simple binary tree (not a BST) to demonstrate structure
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    struct TreeNode* learningRoot = createNode(1);
    learningRoot->left = createNode(2);
    learningRoot->right = createNode(3);
    learningRoot->left->left = createNode(4);
    learningRoot->left->right = createNode(5);

    printf("This is a sample binary tree structure.\n");
    printf("Root: The top node (value 1).\n");
    printf("Parent of 4 and 5 is 2.\n");
    printf("Children of 2 are 4 and 5.\n");
    printf("Leaves: Nodes with no children (4, 5, 3).\n");
    printf("Siblings: Nodes with the same parent (2 and 3 are siblings).\n\n");

    printf("--- Tree Traversal Demonstrations (on the learning tree) ---\n");
    printf("In-order (Left, Root, Right): ");
    inOrderTraversal(learningRoot);
    printf("\n");

    printf("Pre-order (Root, Left, Right): ");
    preOrderTraversal(learningRoot);
    printf("\n");

    printf("Post-order (Left, Right, Root): ");
    postOrderTraversal(learningRoot);
    printf("\n\n");


    printf("--- Binary Search Tree (BST) Implementation ---\n");
    struct TreeNode* bstRoot = NULL; // Start with an empty tree

    // 2. Insert nodes into the BST
    bstRoot = insertNode(bstRoot, 50);
    insertNode(bstRoot, 30);
    insertNode(bstRoot, 20);
    insertNode(bstRoot, 40);
    insertNode(bstRoot, 70);
    insertNode(bstRoot, 60);
    insertNode(bstRoot, 80);

    printf("BST created by inserting: 50, 30, 20, 40, 70, 60, 80\n");
    printf("In-order traversal of the BST (should be sorted): ");
    inOrderTraversal(bstRoot);
    printf("\n\n");

    // 3. Search for nodes in the BST
    printf("--- BST Search ---\n");
    int keyToSearch = 40;
    struct TreeNode* foundNode = searchNode(bstRoot, keyToSearch);
    if (foundNode != NULL) {
        printf("Node with value %d found in the BST.\n", keyToSearch);
    } else {
        printf("Node with value %d not found in the BST.\n", keyToSearch);
    }

    keyToSearch = 90;
    foundNode = searchNode(bstRoot, keyToSearch);
    if (foundNode != NULL) {
        printf("Node with value %d found in the BST.\n", keyToSearch);
    } else {
        printf("Node with value %d not found in the BST.\n", keyToSearch);
    }
    printf("\n");

    // 4. Delete nodes from the BST
    printf("--- BST Deletion ---\n");

    // Case 1: Deleting a leaf node (20)
    printf("Deleting 20 (a leaf node)...\n");
    bstRoot = deleteNode(bstRoot, 20);
    printf("In-order traversal after deleting 20: ");
    inOrderTraversal(bstRoot);
    printf("\n\n");

    // Case 2: Deleting a node with one child (30)
    printf("Deleting 30 (node with one right child)...\n");
    bstRoot = deleteNode(bstRoot, 30);
    printf("In-order traversal after deleting 30: ");
    inOrderTraversal(bstRoot);
    printf("\n\n");

    // Case 3: Deleting a node with two children (50)
    printf("Deleting 50 (root node with two children)...\n");
    bstRoot = deleteNode(bstRoot, 50);
    printf("In-order traversal after deleting 50: ");
    inOrderTraversal(bstRoot);
    printf("\n\n");
    
    // Free the remaining nodes (good practice)
    // A post-order traversal is suitable for freeing memory
    // (This part is for cleanup, not part of the core logic demonstration)

    return 0;
}

/**
 * @brief Allocates a new TreeNode with the given data.
 * @param data The integer value for the new node.
 * @return A pointer to the newly created TreeNode.
 */
struct TreeNode* createNode(int data) {
    // Allocate memory for the new node
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    // Assign data and initialize children to NULL
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 2. Recursive Tree Traversal Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * @brief Performs an in-order traversal of a binary tree (Left, Root, Right).
 * For a BST, this results in a sorted list of node values.
 * @param root The root of the tree (or subtree) to traverse.
 */
void inOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

/**
 * @brief Performs a pre-order traversal of a binary tree (Root, Left, Right).
 * Useful for creating a copy of the tree.
 * @param root The root of the tree (or subtree) to traverse.
 */
void preOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

/**
 * @brief Performs a post-order traversal of a binary tree (Left, Right, Root).
 * Useful for deleting nodes from the tree.
 * @param root The root of the tree (or subtree) to traverse.
 */
void postOrderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 3. Binary Search Tree (BST) Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * @brief Recursively inserts a new node into a BST.
 * It maintains the BST property: node->left->data < node->data < node->right->data.
 * @param root The root of the BST.
 * @param data The integer value to insert.
 * @return The root of the modified BST.
 */
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    // Base case: If the tree is empty, create a new node and return it as the new root.
    if (root == NULL) {
        return createNode(data);
    }

    // Recursive step:
    // If data is smaller, go to the left subtree.
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } 
    // If data is larger, go to the right subtree.
    else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    // If data is equal, do nothing (or handle as per requirements, e.g., update).
    // Here we simply return the unchanged root pointer.

    return root;
}

/**
 * @brief Recursively searches for a node with a given value in a BST.
 * @param root The root of the BST.
 * @param data The value to search for.
 * @return A pointer to the found node, or NULL if not found.
 */
struct TreeNode* searchNode(struct TreeNode* root, int data) {
    // Base cases:
    // 1. Root is NULL, or the key is present at the root.
    if (root == NULL || root->data == data) {
        return root;
    }

    // Recursive step:
    // If the data is greater than the root's data, search in the right subtree.
    if (data > root->data) {
        return searchNode(root->right, data);
    }
    
    // If the data is smaller than the root's data, search in the left subtree.
    return searchNode(root->left, data);
}

/**
 * @brief Finds the node with the minimum value in a given tree (the inorder successor).
 * In a BST, this is the leftmost node.
 * @param node The root of the tree to search.
 * @return A pointer to the node with the minimum value.
 */
struct TreeNode* findMinValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    // Loop down to find the leftmost leaf
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


/**
 * @brief Deletes a node with the given key from the BST.
 * Handles three cases:
 * 1. The node to be deleted is a leaf node.
 * 2. The node has only one child.
 * 3. The node has two children.
 * @param root The root of the BST.
 * @param data The value of the node to delete.
 * @return The root of the modified BST.
 */
struct TreeNode* deleteNode(struct TreeNode* root, int data) {
    // Base case: If the tree is empty, return NULL.
    if (root == NULL) {
        return root;
    }

    // Recursively find the node to delete
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } 
    // If the key is the same as the root's key, then this is the node to be deleted
    else {
        // CASE 1: Node with only one child or no child (leaf)
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp; // The right child (or NULL) becomes the new root of this subtree
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp; // The left child becomes the new root of this subtree
        }

        // CASE 2: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        struct TreeNode* temp = findMinValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor from the right subtree
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
