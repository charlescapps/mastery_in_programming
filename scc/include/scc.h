#ifndef _SCC
#define _SCC

#include "list.h"
#include "misc.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct vertex_struct vertex; 

typedef struct vertex_struct {

	int name; 
	int tarjan_num; 
	int tarjan_low;
 
	list* adjlist; 

} v_struct; 

vertex* new_vertex(int name);

void free_vertex(void*); 

vertex* build_graph_from_stdin(list* v_list); //Function to build a graph from stdin. Takes an empty list of vertices and populates it. 
												//Return value is the entry-point vertex, i.e. the first vertex entered. 

void get_sccs(vertex* entry, list* sccs, list* graph); //Finds SCCs starting at the given entry point. Populates list* sccs with the SCCs. 

void get_sccs_helper(vertex* entry, list* sccs, list* stack, list* graph); //Tarjan's algorithm. Populates a list of lists of nodes, i.e. a list of vertices for each SCC. 

vertex* contains_vertex(int name, list* v_list); //Takes a graph, i.e. a list of vertices. Returns NULL if that name isn't present, returns the vertex otherwise

vertex* has_edge_to(int name, vertex* v); //Returns the vertex if the vertex v contains an edge to vertex 'name', otherwise returns NULL

void print_graph(list* graph); //Prints a graph in simple form

void print_sccs(list* sccs); //Prints the list of SCCs. Input must be a list of lists of vertices, i.e. a collection of SCCs

void print_nontrivial_sccs(list* sccs); //Prints the list of SCCs. Input must be a list of lists of vertices, i.e. a collection of SCCs

#endif
