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
	vertex* v_tmp1; 
	vertex* v_tmp2; 

	while (fgets(buffer, MAX_LINE_SIZE, stdin)) {//While we haven't reached EOF
		name1 = name2 = -1; 
		sscanf(buffer, "%d %d\n", &name1, &name2); 
		if (name1 < 0 || name2 < 0) {
			printf("Invalid input. Skipping to next line\n"); 
			continue; 
		}
		//printf("name 1: %d, name 2: %d\n", name1, name2); 

		if ( !(v_tmp1 = contains_vertex(name1, v_list)) ) {//If the first number isn't in the vertex list
			add_to_list(v_list, (v_tmp1 = new_vertex(name1)) ); 
		}
		if (!(v_tmp2 = contains_vertex(name2, v_list))) {//If the second number isn't in the vertex list
			add_to_list(v_list, (v_tmp2 = new_vertex(name2)) ); 
		}

		if (entry == NULL) {//If the entry-point vertex (first one entered) is NULL, set it
			entry = v_tmp1; 
		}

		if (!has_edge_to(name2, v_tmp1)) { //If there's no edge from name1 to name2, add it
			add_to_list(v_tmp1->adjlist, v_tmp2); 
		}
		else {
			printf("Warning: input specifies edge (%d, %d) twice!\n", name1, name2); 
		}
	}

	return entry; 
}

void get_sccs(vertex* v, list* sccs, int num, list* stack, list* graph) { //Tarjan's algorithm. Populates a list of lists of nodes, i.e. a list of vertices for each SCC. 

	if (v == NULL || sccs == NULL || stack == NULL || graph == NULL) {
		fprintf(stderr, "Error: get_sccs passed a NULL list to populate!\n");
		return;  
	}

	v->tarjan_low = v->tarjan_num = ++num; //Increment "global" integer num and assign to lowlink and number
	
	add_to_list(stack, v); //Add entry to top of stack	

	node* tmp = v->adjlist->head; 
	vertex* w; 

	while (tmp != NULL) { //For each vertex in adjacency list of v
		w = (vertex*)(tmp->data); 
		if (w->tarjan_num < 0) { //If it's undiscovered
			get_sccs(w, sccs, num, stack, graph); 
			v->tarjan_low = MIN(v->tarjan_low, w->tarjan_low); 
		}
		else if (w->tarjan_num < v->tarjan_num) {
			if (contains_vertex(w->name, stack)) {//If w is on the stack somewhere
				v->tarjan_low = MIN(v->tarjan_low, w->tarjan_num); 
			}			
		}
		tmp = tmp->next; 
	}	

	if (v->tarjan_num == v->tarjan_low) {
		add_to_list(sccs, new_list(&free_vertex)); //Add a new SCC to the list of SCCs
		list* new_scc = (list*)(sccs->head->data); //Head of list is the new SCC 
		vertex* w; 
		while ( (stack -> head != NULL) ) {
			w = (vertex*)(stack->head->data);
			if (w->tarjan_num >= v->tarjan_num) { //Keep popping top of stack and adding to new_scc as long as condition holds
				add_to_list(new_scc, pop(stack)); 
			} 
			else {
				break; 
			}
		}
	}

	num = 0; 
	free_list(stack); 
	stack = new_list(&free_vertex); 
	node* n = graph->head;
	while (n != NULL) { //Call get_sccs on other connected components of the graph
		v = (vertex*)(n->data);
		if (v->tarjan_num < 0) {
			get_sccs(v, sccs, num, stack, graph); 
		} 	
		n = n->next; 
	} 

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

void print_graph(list* graph) { //Prints a graph in simple form
	 if (graph == NULL) {
		fprintf(stderr, "Error: NULL graph passed to print_graph.\n"); 
		return; 	
	}	

	node* tmp = graph->head; 
	node* adj_list_tmp; 
	vertex* v; 

	while (tmp != NULL) {
		v = (vertex*)(tmp->data); 
		printf("Node %d Adjacency List: ", v->name); 
		adj_list_tmp = v->adjlist->head; 
		while (adj_list_tmp != NULL) {
			printf("(%d)", ((vertex*)(adj_list_tmp->data))->name); 
			if (adj_list_tmp -> next != NULL) {
				printf(", "); 
			}
			adj_list_tmp = adj_list_tmp -> next; 
		}
		printf("\n"); 
		tmp = tmp->next; 	
	}



}
