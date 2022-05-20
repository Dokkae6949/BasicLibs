#ifndef BASICLIST_H
#define BASICLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
//  [HEAD] -> [NODE] -> [NODE] -> [NODE] -> [NODE] -> [NULL] 
//


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


size_t lst_GetNodeSize(const size_t dataSize);

void lst_PrependNewNode(Lst_List *list, const int key, void *data, const size_t dataSize, Lst_Node *nextNode);

void lst_AppendNewNode(Lst_List *list, const int key, void *data, const size_t dataSize, Lst_Node *nextNode);

Lst_Node* lst_GetNode(const Lst_List *list, const int key);

void lst_FreeNode(Lst_Node *node);

void lst_FreeList(Lst_List *list);

void lst_DestroyNode(Lst_List *list, const int key);

size_t lst_GetListLength(Lst_List *list);

#endif