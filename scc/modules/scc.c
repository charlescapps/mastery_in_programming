#include "../include/scc.h"

static const int MAX_LINE_SIZE = 128; //User shouldn't need to enter 128 chars! 

vertex* new_vertex(int name) {
	vertex* v = (vertex*)malloc(sizeof(vertex)); 
	v->name = name; 
	v->adjlist = new_list(&free_vertex); //Initialize a new linked list that knows how to free its nodes
	v->tarjan_num = -1; 
	v->tarjan_low = -1; 

	return v; 
}

void free_vertex(void* v) {
	free(v); 
} 

vertex* build_graph_from_stdin(list* v_list) { //Function to build a graph from stdin. Takes an empty list of vertices and populates it. 
												//Return value is the entry-point vertex, i.e. the first vertex entered. 
	printf("Enter pairs of vertex names to build a graph, e.g. \"1 4\" to create an edge from node 1 to node 4.\nTerminate input with ctrl+d.\n"); 

	char buffer[MAX_LINE_SIZE]; 
	int name1 = -1, name2 = -1; 
	vertex* entry = NULL; 

	while (fgets(buffer, MAX_LINE_SIZE, stdin)) {//While we haven't reached EOF
		sscanf(buffer, "%d %d\n", &name1, &name2); 
		printf("name 1: %d, name 2: %d\n", name1, name2); 
	}

	return entry; 
}

vertex* contains_vertex(int name_to_find, list* v_list) { //Takes a graph, i.e. a list of vertices. Returns NULL if that name isn't present, returns the vertex otherwise
	node* tmp = v_list->head;
	vertex* v_tmp; 
	while (tmp != NULL) {
		v_tmp = (vertex*)(tmp->data); 
		if ( v_tmp != NULL && v_tmp->name == name_to_find) {
			return v_tmp; 
		}
		tmp = tmp->next; 
	} 
	return NULL; 
}

vertex* has_edge_to(int name_to_find, vertex* v){ //Returns true IFF the vertex v contains an edge to 'name'
	node* tmp = v->adjlist->head;
	vertex* v_tmp; 
	while (tmp!=NULL) {
		v_tmp = (vertex*)(tmp->data);
		if (v_tmp != NULL && v_tmp->name == name_to_find) {
			return v_tmp; 
		}
		tmp = tmp->next;
	} 
	return NULL; 
}
