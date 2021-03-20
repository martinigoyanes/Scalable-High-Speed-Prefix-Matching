#include "tools.h"
#include "io.h"
#include "utils.h"

int buildUp(struct TreeNode** root, int* defaultGateway)
{
   int *numAccesses = (int *)malloc(sizeof(int));
   /* Set up BST with HashTable with separate chaining  at each node */
   *root = createTree();
   uint32_t *prefix = (uint32_t *)malloc(sizeof(uint32_t));
   int *prefixLength = (int *)malloc(sizeof(int));
   int *outInterface = (int *)malloc(sizeof(int));
   int *netmask = (int *)malloc(sizeof(int));
   struct Node *aux;
   uint32_t mask = 0;
   int error = OK, index = 0;
   struct TreeNode *current;
   *defaultGateway = 0;
   /* Read entry by entry from the routing table */
   while((error = readFIBLine(prefix, prefixLength, outInterface)) == OK)   { 
      current = *root;
      // Get default gateway
      if(*prefixLength == 0)
         *defaultGateway = *outInterface;
      while(1){
         *netmask = 0;index = 0;
         if(*prefixLength > current->len)
         {
            //calculate hash index
            getNetmask(current->len, netmask);
            mask = *prefix & *netmask;
            index = hash(mask, SIZE);
            //create a newnode 
            struct Node *newNode = malloc(sizeof(struct Node));
            newNode->mask = mask;
            //check if table[index] is empty
            if(current->table[index].head == NULL)
            {
               // Creating a prefix-marker since len(mask) > node.len
               newNode->outInterface = lookUp(mask, current->left, numAccesses, defaultGateway);
               newNode->marker = 1;
               newNode->next = NULL;
               current->table[index].head = newNode;
            }
            //collision
            else
            {
               //add the node at the end of table[index].
               aux = current->table[index].head;
               while(aux->next)
               {
                  // Updating mask at Node.table[hash(mask)], make it a marker
                  if(aux->mask == mask)
                  {
                     aux->marker = 1;
                     break;
                  }
                  aux = aux->next;
               }

               if(aux->mask == mask) // mask  found in last bucket
               {
                  aux->marker = 1;
               }
               else
               {
                  // Creating a prefix-marker since len(mask) > node.len
                  newNode->outInterface = lookUp(mask, current->left, numAccesses, defaultGateway);
                  newNode->marker = 1;
                  newNode->next = NULL;
                  aux->next = newNode;
               }
            }
            current = current->right;

         }else if(*prefixLength < current->len)
         {
            current = current->left;
         }else
         {
            //calculate hash index
            getNetmask(current->len, netmask);
            mask = *prefix & *netmask;
            index = hash(mask, SIZE);
            //create a newnode 
            struct Node *newNode = malloc(sizeof(struct Node));
            newNode->mask = mask;
            //check if table[index] is empty
            if(current->table[index].head == NULL)
            {
               // Creating a prefix-marker since len(mask) > node.len
               newNode->outInterface = *outInterface;
               newNode->marker = 0;
               newNode->next = NULL;
               current->table[index].head = newNode;
            }
            //collision
            else
            {
               //add the node at the end of table[index].
               aux = current->table[index].head;
               while(aux->next)
               {
                  aux = aux->next;
               }

               // Creating a prefix entry since len(mask) == node.len
               newNode->outInterface = *outInterface;
               newNode->marker = 0;
               newNode->next = NULL;
               aux->next = newNode;

            }
            break;
         }
      }
   }

   // Free used memory
   free(numAccesses);
   free(prefix);
   free(prefixLength);
   free(outInterface);
   free(netmask);

   return error;   
}

int lookUp(uint32_t IPAddress, struct TreeNode* root, int* numOfTableAccesses, int *defaultGateway)
{
   int *netmask = (int *)malloc(sizeof(int));
   uint32_t mask = 0;int bmp = 0;
   struct TreeNode* current = root;
   struct Node* cell = NULL;

   while(current){
      getNetmask(current->len, netmask);
      mask = IPAddress & *netmask;
      *numOfTableAccesses = *numOfTableAccesses + 1;
      if((cell = searchHT(current->table, mask)) != NULL)   
      {
         // If mask found in node.table[hash(mask)]
         if(cell->outInterface != 0)
            bmp = cell->outInterface;
         if(cell->marker == 1)
         {
            // We have to keep going to the right is just a marker
            current = current->right;
         }else
         {
            // We found LPM
            break;
         }
      }else
      {
         if(current->len == 1)
         {
            // Free used memory
            free(netmask);
            return *defaultGateway;
         }
         // MISS -> go left
         current = current->left;
      }
   }
   // Free used memory
   free(netmask);
   return bmp;
}

void freeTree(struct TreeNode** root){
   struct TreeNode * node = *root;
   struct TreeNode * up = NULL;

   while (node != NULL) {
      if (node->left != NULL) {
         struct TreeNode * left = node->left;
         node->left = up;
         up = node;
         node = left;
      } else if (node->right != NULL) {
         struct TreeNode * right = node->right;
         node->left = up;
         node->right = NULL;
         up = node;
         node = right;
      } else {
         if (up == NULL) {
            freeHT(node->table);
            free(node->table);
            free(node);
            node = NULL;
         }
         while (up != NULL) {
            freeHT(node->table);
            free(node->table);
            free(node);
            if (up->right != NULL) {
               node = up->right;
               up->right = NULL;
               break;
            } else {
               node = up;
               up = up->left;
            }
         }
      }
   }
}

struct TreeNode* createTree(){

   struct TreeNode* node_0  = createNode(0); 
   struct TreeNode* node_1  = createNode(1); 
   struct TreeNode* node_2  = createNode(2); 
   struct TreeNode* node_3  = createNode(3); 
   struct TreeNode* node_4  = createNode(4); 
   struct TreeNode* node_5  = createNode(5); 
   struct TreeNode* node_6  = createNode(6); 
   struct TreeNode* node_7  = createNode(7); 
   struct TreeNode* node_8  = createNode(8); 
   struct TreeNode* node_9  = createNode(9); 
   struct TreeNode* node_10  = createNode(10); 
   struct TreeNode* node_11  = createNode(11); 
   struct TreeNode* node_12  = createNode(12); 
   struct TreeNode* node_13  = createNode(13); 
   struct TreeNode* node_14  = createNode(14); 
   struct TreeNode* node_15  = createNode(15); 
   struct TreeNode* node_16  = createNode(16); 
   struct TreeNode* node_17  = createNode(17); 
   struct TreeNode* node_18  = createNode(18); 
   struct TreeNode* node_19  = createNode(19); 
   struct TreeNode* node_20  = createNode(20); 
   struct TreeNode* node_21  = createNode(21); 
   struct TreeNode* node_22  = createNode(22); 
   struct TreeNode* node_23  = createNode(23); 
   struct TreeNode* node_24  = createNode(24); 
   struct TreeNode* node_25  = createNode(25); 
   struct TreeNode* node_26  = createNode(26); 
   struct TreeNode* node_27  = createNode(27); 
   struct TreeNode* node_28  = createNode(28); 
   struct TreeNode* node_29  = createNode(29); 
   struct TreeNode* node_30  = createNode(30); 
   struct TreeNode* node_31  = createNode(31); 
   struct TreeNode* node_32  = createNode(32); 

   node_1->left = node_0;

   node_2->left = node_1;
   node_2->right = node_3;

   node_6->left = node_5;
   node_6->right = node_7;

   node_4->left = node_2;
   node_4->right = node_6;

   node_10->left = node_9;
   node_10->right = node_11;

   node_14->left = node_13;
   node_14->right = node_15;

   node_12->left = node_10;
   node_12->right = node_14;

   node_8->left = node_4;
   node_8->right = node_12;

   node_18->left = node_17;
   node_18->right = node_19;

   node_22->left = node_21;
   node_22->right = node_23;

   node_26->left = node_25;
   node_26->right = node_27;

   node_30->left = node_29;
   node_30->right = node_31;

   node_31->right = node_32;

   node_20->left = node_18;
   node_20->right = node_22;

   node_28->left = node_26;
   node_28->right = node_30;

   node_16->left = node_8;
   node_16->right = node_20;

   node_24->left = node_16;
   node_24->right = node_28;

   return node_24;
}
