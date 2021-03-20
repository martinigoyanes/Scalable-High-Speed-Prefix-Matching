#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1033 // Prime number so hash() works better

struct Node
{
    uint32_t mask;
    int outInterface;
    uint8_t marker;
    struct Node *next;
};

struct Table{
   struct Node *head;
};

struct Table* initHT();
struct Node* searchHT(struct Table *table, uint32_t mask);
void printHT(struct Table *table);
void freeHT(struct Table *table);
