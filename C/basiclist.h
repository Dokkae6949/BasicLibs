#ifndef BASICLIST_H
#define BASICLIST_H

#include <stdio.h>
#include <stdlib.h>

#pragma region Struct definitions
#define LST_INTERNAL__NODE(name, dataType) \
    typedef struct Node_##name \
    { \
        int key; \
        dataType data; \
        struct Node_##name *next; \
    }Node_##name; 

#define LST_INTERNAL__LIST(name, nodeType) \
    typedef struct List_##name \
    { \
        nodeType *head; \
    }List_##name;
#pragma endregion Struct definitions

#pragma region LST_INTERNAL definitions
// Adds node to the very front of the list
#define LST_INTERNAL__LST_ADD_NODE(listType, nodeType, dataType) \
    void lst_AddNode_##listType(listType *list, int newKey, nodeType node) \
    { \
        nodeType *newNode = (nodeType*) malloc(sizeof(nodeType)); \
        if (newNode == NULL) return; \
        newNode->key = newKey; \
        newNode->data = node.data; \
        newNode->next = list->head; \
        list->head = newNode; \
    }

// Tries to remove node with given key from list and frees memory location
#define LST_INTERNAL__LST_DESTROY_NODE(listType, nodeType) \
    void lst_DestroyNode_##listType(listType *list, int key) \
    { \
        if (list->head == NULL) return; \
        nodeType *currentNode = list->head; \
        nodeType *lastNode = NULL; \
        while (currentNode->key != key) \
        { \
            if (currentNode->next == NULL) return; \
            lastNode = currentNode; \
            currentNode = currentNode->next; \
        } \
        if (currentNode == list->head) \
            list->head = list->head->next; \
        else \
            lastNode->next = currentNode->next; \
        free(currentNode); \
    }

// Tries to find a node given the key of it and returns a pointer to it
#define LST_INTERNAL__LST_GET_NODE(listType, nodeType) \
    nodeType* lst_GetNode_##listType(listType *list, int key) \
    { \
        if (list->head == NULL) return NULL; \
        nodeType *currentNode = list->head; \
        while (currentNode->key != key)\
        { \
            if (currentNode->next == NULL) return NULL; \
            currentNode = currentNode->next; \
        } \
        return currentNode; \
    }

// Returns the lenght of the list
#define LST_INTERNAL__LST_GET_LENGHT(listType) \
    size_t lst_GetLenght_##listType(listType *list) \
    { \
        size_t length = 0; \
        typeof(list->head) currentNode = list->head; \
        while (currentNode != NULL) \
        { \
            length++; \
            currentNode = currentNode->next; \
        } \
        return length; \
    }
#pragma endregion LST_INTERNAL definitions


// #################################################
// #################################################


// Creates and sets up every function for a new list type
#define LIST_SETUP(name, dataType) \
    LST_INTERNAL__NODE(name, dataType) \
    LST_INTERNAL__LIST(name, Node_##name) \
    LST_INTERNAL__LST_ADD_NODE(List_##name, Node_##name, Monte) \
    LST_INTERNAL__LST_DESTROY_NODE(List_##name, Node_##name) \
    LST_INTERNAL__LST_GET_NODE(List_##name, Node_##name) \
    LST_INTERNAL__LST_GET_LENGHT(List_##name)


// ############################
// #### DEFAULT LIST TYPES ####
// ############################

LIST_SETUP(Char, char)
LIST_SETUP(Short, short)
LIST_SETUP(Int, int)
LIST_SETUP(Unsigned, unsigned)
LIST_SETUP(Long, long)
LIST_SETUP(Float, float)
LIST_SETUP(Double, double)

#endif