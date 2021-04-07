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
