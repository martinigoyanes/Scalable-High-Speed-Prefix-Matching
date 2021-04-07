#include "binarytree.h"

struct TreeNode* createTree();
int buildUp(struct TreeNode** root, int* defaultGateway);
int lookUp(uint32_t IPAddress, struct TreeNode* root, int* numOfTableAccesses, int* defaultGateway);
void freeTree(struct TreeNode** root);

