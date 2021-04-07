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

