#include "include/list.h"
#include "include/scc.h"

/*
Implementation of Tarjan's SCC Algorithm 
Charles L. Capps
Homework 5 of CS 510: Mastery in Programming

Decided to avoid using global variables, so the algorithm requires passing in an empty list / stack / initial number. 
This way a helper function is also unnecessary. 

Also of interest, my list module is a generic linked list that takes any kind of data. new_list takes a function pointer to 
the function that frees the data in a node. It's the client program's responsibility to only put the same kind of data in 
a given list! This is nice, though, because in this way I can re-use my list class in any C program. 

*/

int main() {

	list* v_list = new_list(&free_vertex); 
	vertex* entry = build_graph_from_stdin(v_list); 

	print_graph(v_list); 

	list* sccs = new_list(&free_list); //Create a new list of lists. Function to free a list is the free list function
	list* stack = new_list(&free_vertex); //Create a new list of vertices to act as the stack

	get_sccs(entry, sccs, 0, stack, v_list); 

	return 0; 
}
