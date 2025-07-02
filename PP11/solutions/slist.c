#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

static SNode* create_snode(int value){
	SNode *newNode = (SNode*)malloc(sizeof(SNode));
	newNode->value = value;
	newNode -> next = NULL;
	return newNode;
}

SNode* add_node(SNode *head, int value ){
	SNode *newNode = create_snode(value);
	newNode->next = head;
	return newNode; 
}

int count_nodes(SNode *head) {
    int count = 0;
    SNode *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void free_list(SNode *head) {
    if ( head == NULL) {
        return;
    }

    SNode *current = head;
    SNode *next_node;

    while (current != NULL) {
	next_node = current->next;
	free(current);   
	current = next_node; 
    }
    head = NULL;  
}

 
