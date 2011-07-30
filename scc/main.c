#include "include/list.h"
#include "include/scc.h"

int main() {

	list* v_list = new_list(&free_vertex); 
	vertex* entry = build_graph_from_stdin(v_list); 
	return 0; 
}
