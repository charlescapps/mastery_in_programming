#ifndef _LIST
#define _LIST

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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

void* pop(list* l); //Removes from front without freeing data. Returns data that was at front. 

void free_list(void* l); //Free up list

void free_nodes(list* l); //Free the nodes in a list, without freeing the data in each node. 
						//This is useful in the SCC homework, since we want to free up the stack w/o deleting the graph!!!

bool is_empty(list* l); 

int list_size(list* l); //Returns number of nodes in list. 

#endif
