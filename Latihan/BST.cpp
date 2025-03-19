#include <stdio.h>
#include <stdlib.h>

// Definition of a node in the BST
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node *insert(struct Node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }

    if (value < root->data)
    {
        root->left = insert(root->left, value);
    }
    else if (value > root->data)
    {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to find the inorder predecessor (rightmost node in the left subtree)
struct Node *findPredecessor(struct Node *root)
{
    struct Node *current = root;
    while (current && current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

// Function to delete a node using the inorder predecessor
struct Node *deleteNode(struct Node *root, int key)
{
    if (root == NULL)
    {
        return root;
    }

    // Search for the node to delete
    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        // Node found

        // Case 1: No children (leaf node)
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        // Case 2: One child
        if (root->left == NULL)
        {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        struct Node *temp = findPredecessor(root->left); // Find inorder predecessor
        root->data = temp->data;                         // Replace node data with predecessor’s data
        root->left = deleteNode(root->left, temp->data); // Delete predecessor
    }
    return root;
}

// Function to search for a value in the BST
struct Node *search(struct Node *root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Function for in-order traversal (Left, Root, Right)
void inorderTraversal(struct Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Menu-driven program
int main()
{
    struct Node *root = NULL;
    int choice, value;

    do
    {
        printf("\nBinary Search Tree Menu:\n");
        printf("1. Insert\n");
        printf("2. Delete (using Inorder Predecessor)\n");
        printf("3. Search\n");
        printf("4. View (In-order Traversal)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            printf("%d inserted successfully.\n", value);
            break;

        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            printf("%d deleted successfully (if it existed).\n", value);
            break;

        case 3:
            printf("Enter value to search: ");
            scanf("%d", &value);
            if (search(root, value) != NULL)
                printf("%d found in BST.\n", value);
            else
                printf("%d not found in BST.\n", value);
            break;

        case 4:
            printf("BST in-order traversal: ");
            inorderTraversal(root);
            printf("\n");
            break;

        case 5:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
