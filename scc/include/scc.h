#ifndef _SCC
#define _SCC

#include "list.h"
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

vertex* contains_vertex(int name, list* v_list); //Takes a graph, i.e. a list of vertices. Returns NULL if that name isn't present, returns the vertex otherwise

vertex* has_edge_to(int name, vertex* v); //Returns the vertex if the vertex v contains an edge to vertex 'name', otherwise returns NULL

#endif
