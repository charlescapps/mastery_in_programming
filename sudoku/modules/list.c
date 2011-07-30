#include "../include/list.h"

node* new_node(void* data) {
	node* n = (node*)malloc(sizeof(node)); 
	n->data = data; 
	n->next = NULL; 
	return n; 
}

list* new_list(void (*free_fnc)(void*)) {
	list* l = (list*) malloc(sizeof(list)); 
	l->free_data = free_fnc; 
	l->head = NULL; 
	return l; 
}

void add_to_list(list* l, void* data) { //Adds node to list and returns the new head
	node* new_head = new_node(data); 
	new_head -> next = l->head; 
	l->head = new_head; 
}

void remove_front(list* l) { //Removes a node from the front and frees the data
	if (l->head == NULL) {
		return; 
	}

	node* old_head = l->head; 
	l->head = old_head->next; 
	(*(l->free_data))(old_head); //Call function to free the old head
}
