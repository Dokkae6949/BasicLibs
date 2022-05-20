#include <stdio.h>
#include "basiclist.h"

// Custom data type
typedef struct Data
{
    int x;
    int y;
}Data;

int main()
{
    // Initializing new list
    Lst_List list = {NULL, NULL};
    
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
    
    // Destroys all the nodes and frees them
    // (Lst_)List itself will not be destroyed and can be used again
    lst_FreeList(&list);
    
    return 0;
}