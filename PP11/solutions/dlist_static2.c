#include <stdio.h>
#include "dlist2.h"  // defines DNode and DList

// Static nodes for values 1–5
DNode nodes[5];
DList list;

int main(void) {
    // Initialize static nodes
    for (int i = 0; i < 5; i++) {
        nodes[i].number = i + 1; 		  //Assigning a number
        sprintf (nodes[i].name, "Name %d", i+1); //Assigning a name  

        nodes[i].prev = (i > 0) ? &nodes[i - 1] : NULL;
        nodes[i].next = (i < 4) ? &nodes[i + 1] : NULL;
    }
    list.head = &nodes[0];
    list.tail = &nodes[4];

    // Traverse forward
    printf("Forward:\n ");
    printf("Number\n\tName\n");
    printf("------\t--------\n");	
    for (DNode *p = list.head; p != NULL; p = p->next) {
         printf("%d\t%-15s\t ",p->number, p->name);
    }
    printf("\n");

    // Traverse backward
    printf("Backward:\n ");
    printf("Number\n\tName\n");
    printf("------\t--------\n");
    for (DNode *p = list.tail; p != NULL; p = p->prev) {
        printf("%d\t%-15s\t ",p->number, p->name);
    }
    printf("\n");

    return 0;
}
