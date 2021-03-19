#include "hashtable.h"
#include "utils.h"

struct Table* initHT()
{
    struct Table *table = (struct Table *)malloc(sizeof(struct Table) * SIZE);
    for(int i = 0; i < SIZE; i++)
        table[i].head = NULL;
    return table;
}


/*
 * return entry, search found
 * return NULL, Otherwise
 */
struct Node* searchHT(struct Table *table, uint32_t mask)
{
    int index = hash(mask, SIZE); 
    struct Node *temp = table[index].head;
    while(temp)
    {
        if(temp->mask == mask)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void printHT(struct Table *table)
{
    for(int i = 0; i < SIZE; i++)
    {
        struct Node *temp = table[i].head;
        printf("table[%d]-->",i);
        while(temp)
        {
            printf("[%u, %d, %u] -->",temp->mask, temp->outInterface, temp->marker);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

