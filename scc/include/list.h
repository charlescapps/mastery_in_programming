#ifndef _LIST
#define _LIST

#include <stdlib.h>
#include <stdbool.h>

typedef struct node_struct node; //Forward declaration so a list can have a next pointer

typedef struct node_struct { //Node type. Holds arbitrary data

	void* data; 
	node* next; 

} node_str; 

typedef struct { //List type

	node* head; 

	void (*free_data)(void*); //Function telling list how to free a node

} list;

node* new_node(void* data); 

list* new_list(void (*free_fnc)(void*)); 

void add_to_list(list* l, void* data); //Adds node to list and returns the new head

void remove_front(list* l); //Removes a node from the front and frees the data

bool is_empty(list* l); 

#endif
