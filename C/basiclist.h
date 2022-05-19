#ifndef BASICLIST_H
#define BASICLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//  [HEAD] -> [NODE] -> [NODE] -> [NODE] -> [NODE] -> [NULL] 
//
/* EXAMPLE CODE
===============

#include "basiclist.h"

typedef struct Data
{
    int x;
    int y;
}Data;

int main()
{
    // Initializing new list
    Lst_List list = {NULL, NULL} 
    
    // Creating data
    Data data = {17, 16};
    // Linking data || List, Key, Data, DataSize,     NextNode
    lst_AppendNewNode(&list, 0,  &data, sizeof(data), NULL);
    
    // Find node ||               List, Key
    Lst_Node *node = lst_GetNode(&list, 0);
    // Make sure node has been found
    if (node != NULL)
    {
        // Cast void* back to Data* and print
        Data data = *(Data*) node->data;
        printf("%d - %d\n", data.x, data.y);
    }
    
    return 0;
}
=======>
OUTPUT:
 17 - 16
===============
*/

typedef struct Lst_Node 
{ 
    int key;
    void *data;
    size_t dataSize;
    struct Lst_Node *next;
}Lst_Node; 

typedef struct Lst_List
{
    Lst_Node *head;
    Lst_Node *tail;
}Lst_List;


size_t lst_GetNodeSize(const size_t dataSize)
{
    return sizeof(Lst_Node) - sizeof(dataSize) + dataSize;
}

void lst_PrependNewNode(Lst_List *list, const int key, void *data, const size_t dataSize, Lst_Node *nextNode)
{
    if (list == NULL) return;

    Lst_Node *newNode = (Lst_Node*) malloc(lst_GetNodeSize(dataSize));

    if (newNode == NULL) return;

    newNode->key = key;
    newNode->data = malloc(dataSize);
    newNode->dataSize = dataSize;
    newNode->next = nextNode;

    for(int i=0; i < dataSize; i++)
        *(char *)(newNode->data + i) = *(char *)(data + i);

    if (list->tail == NULL) 
        list->tail = newNode;
    newNode->next = list->head;
    list->head = newNode;
}

void lst_AppendNewNode(Lst_List *list, const int key, void *data, const size_t dataSize, Lst_Node *nextNode)
{
    if (list == NULL) return;

    Lst_Node *newNode = (Lst_Node*) malloc(lst_GetNodeSize(dataSize));

    if (newNode == NULL) return;
    
    newNode->key = key;
    newNode->data = malloc(dataSize);
    newNode->dataSize = dataSize;
    newNode->next = nextNode;

    for(int i=0; i < dataSize; i++)
        *(char *)(newNode->data + i) = *(char *)(data + i);

    if (list->head == NULL)
        list->head = newNode;
    if (list->tail != NULL)
        list->tail->next = newNode;
    list->tail = newNode;
}

Lst_Node* lst_GetNode(const Lst_List *list, const int key) 
{ 
    if (list->head == NULL) return NULL;

    Lst_Node *currentNode = list->head;

    while (currentNode->key != key)
    {
        if (currentNode->next == NULL) return NULL;
        
        currentNode = currentNode->next;
    }

    return currentNode; 
}

void lst_FreeNode(Lst_Node *node)
{
    if (node == NULL) return;

    free(node->data);
    free(node);
}

void lst_FreeList(Lst_List *list)
{
    Lst_Node *currentNode = list->head;
    Lst_Node *lastNode = NULL;

    while (currentNode != NULL)
    {
        lastNode = currentNode;
        currentNode = currentNode->next;

        lst_FreeNode(lastNode);
    }    
    
    list->head = NULL;
    list->tail = NULL;
}

void lst_DestroyNode(Lst_List *list, const int key) 
{ 
    if (list->head == NULL) return;

    Lst_Node *currentNode = list->head;
    Lst_Node *lastNode = NULL;

    while (currentNode->key != key)
    {
        if (currentNode->next == NULL) return;
        lastNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == list->head)
        list->head = list->head->next;
    else if (currentNode == list->tail)
    {
        list->tail = lastNode;
        lastNode->next = NULL; 
    }
    else
        lastNode->next = currentNode->next;

    lst_FreeNode(currentNode);
}

size_t lst_GetListLength(Lst_List *list) 
{ 
    size_t length = 0;
    typeof(list->head) currentNode = list->head;

    while (currentNode != NULL)
    {
        length++; 
        currentNode = currentNode->next; 
    }
    return length;
}

#endif
