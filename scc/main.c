#include "include/list.h"
#include "include/scc.h"

/*
Implementation of Tarjan's SCC Algorithm 
Charles L. Capps
Homework 5 of CS 510: Mastery in Programming

Decided to avoid using too many global variables, so the algorithm requires passing in an empty list / stack / initial number. 
The only global variable is tarj_number, the number 'i' in Tarjan's Algorithm. 

My list module is a generic linked list that takes any kind of data. new_list takes a function pointer to 
the function that frees the data in a node. It's the client program's responsibility to only put the same kind of data in 
a given list! This is nice, though, because in this way I can re-use my list class in any C program. 

The order the SCCs are printed out may differ from someone else's program. I use linked lists for basically everything, since 
a dynamic array wouldn't give any improvement for this algorithm. Adding to the front of lists reverses the order of elements! 

*/

int main() {

	list* graph = new_list(&free_vertex); 
	vertex* entry = build_graph_from_stdin(graph); 

	//print_graph(graph); 

	list* sccs = new_list(&free_list); //Create a new list of lists. Function to free a list is the free list function

	get_sccs(entry, sccs, graph); 

	printf("All SCCs:\n"); 
	print_sccs(sccs); 

	printf("\nNontrivial SCCs:\n"); 
	print_nontrivial_sccs(sccs); 

	return 0; 
}
