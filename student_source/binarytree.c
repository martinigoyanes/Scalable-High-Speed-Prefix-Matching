#include "binarytree.h"
// Create a new Node
struct TreeNode* createNode(int len) {
   struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
   newNode->table = initHT();
   newNode->len = len;
   newNode->left = NULL;
   newNode->right = NULL;

   return newNode;
}

struct TreeNode* insert(struct TreeNode* root, int len)
{
    // If the tree is empty, assign new node address to root
    if (root == NULL) {
        root = createNode(len);
        return root;
    }
    else
    {   
       // Else, do level order traversal until we find an empty
       // place, i.e. either left child or right child of some
       // node is pointing to NULL.
       struct Queue *q = createQueue();
       push(q, root);
    
       while (q->front != NULL) {
           struct TreeNode* temp = q->front->treeNode;
           pop(q);
    
           if (temp->left != NULL)
               push(q, temp->left);
           else {
               temp->left = createNode(len);
               return root;
           }
    
           if (temp->right != NULL)
               push(q, temp->right);
           else {
               temp->right = createNode(len);
               return root;
           }
       }
       return NULL;

   }
}

void print_preorder(struct TreeNode * root)
{
    if (root)
    {
        printf("%d\n",root->len);
        print_preorder(root->left);
        print_preorder(root->right);
    }

}



// A utility function to create a new linked list node.
struct QNode* newNode(struct TreeNode *treeNode)
{
    struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    temp->treeNode = treeNode;
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty queue
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// The function to add a key k to q
void push(struct Queue* q, struct TreeNode *treeNode)
{
    // Create a new LL node
    struct QNode* temp = newNode(treeNode);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove a key from given queue q
void pop(struct Queue* q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return;

    // Store previous front and move front one node ahead
    struct QNode* temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}
