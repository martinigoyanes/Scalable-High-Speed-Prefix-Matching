#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

struct TreeNode {
  int len;
  struct Table* table;
  struct TreeNode* left;
  struct TreeNode* right;
};


struct TreeNode* createNode(int len);
struct TreeNode* insert(struct TreeNode *root, int len);
void print_preorder(struct TreeNode * root);


struct QNode {
    struct TreeNode *treeNode;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
};


struct QNode* newNode(struct TreeNode *treeNode);
struct Queue* createQueue();
void pop(struct Queue* q);
void push(struct Queue* q, struct TreeNode *treeNode);
