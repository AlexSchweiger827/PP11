#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>
#include <stdio.h>

typedef struct DNode {
    void *data;           // Pointer to the actual data
    struct DNode *prev;   // Pointer to the previous node in the list
    struct DNode *next;   // Pointer to the next node in the list
} DNode;

typedef struct DList {
    DNode *head;
    DNode *tail;
    size_t size;
} DList;



#endif
