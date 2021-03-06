#include "basiclist.h"


size_t lst_GetNodeSize(const size_t dataSize)
{
    return sizeof(Lst_Node) + dataSize;
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
