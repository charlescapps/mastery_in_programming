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

void remove_front(list* l) { //Removes a node from the front and frees data
	if (l->head == NULL) {
		return; 
	}

	node* old_head = l->head; 
	l->head = old_head->next; 
	(*(l->free_data))(old_head->data); //Call function to free the old head's data
	free(old_head); 					//Free the node itself
}

void* pop(list* l) { //Removes from front without freeing data
	if (l == NULL || l->head == NULL) {
		return NULL; 
	}

	node* old_head = l->head; 
	l->head = old_head->next; 
	void* the_data = old_head -> data; 
	free(old_head); 

	return the_data; 

}

void free_list(void* the_list) { //Free up list. Takes void* as argument in case we want a list of lists and need to pass this as the free_data function. 
	if (the_list == NULL) {
		return; 
	}	

	list* l = (list*)the_list; 
	node* tmp = l->head; 
	node* to_delete; 

	while (tmp != NULL) {
		(l->free_data)(tmp->data); //Free the data in the node using the list's function pointer
		to_delete = tmp; 
		tmp = tmp->next; 
		free(to_delete); 		//Free the node itself
	}
}

void free_nodes(list* l) { //Free the nodes in a list, without freeing the data in each node. 
	if (l == NULL) {
		return; 
	}

	node* tmp = l->head; 
	node* to_delete; 

	while (tmp != NULL) {
		to_delete = tmp;
		tmp = tmp->next; 
		free(to_delete); 		//Free the node itself
	}
}

bool is_empty(list* l) {
	
	return (l == NULL || l->head == NULL); 
}


int list_size(list* l) { //Returns number of nodes in list. 
	if (l == NULL) {
		fprintf(stderr, "Error: NULL list passed to list_size"); 
		return -1; 
	}

	node* tmp = l->head; 
	int cnt = 0; 

	while (tmp != NULL) {
		cnt++; 
		tmp = tmp -> next; 
	} 

	return cnt; 

}
