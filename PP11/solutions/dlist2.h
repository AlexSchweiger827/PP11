#ifndef DLIST_H
#define DLIST_H

#include <stddef.h>
#include <stdio.h>

typedef struct DNode {
    int number;		  //Integer number new data field
    char name [100];       // character array for name  new data field
    struct DNode *prev;   // Pointer to the previous node in the list
    struct DNode *next;   // Pointer to the next node in the list
} DNode;

typedef struct DList {
    DNode *head;
    DNode *tail;
    size_t size;
} DList;

#endif
