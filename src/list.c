#include "list.h"

List* new_elem(Value value) {

	List *new_node = (List*)malloc(sizeof(List));
	new_node->value.integer = value.integer;
	new_node->value.character = value.character;
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;
}

List* push_elem(List *node, Value value) {
	List *new_node = new_elem(value);
	
	if(node == NULL) {
		return new_node;
	}

	if(node->next != NULL) {
		new_node->next = node->next;
	}

	new_node->prev = node;
	
	if(node->next != NULL) {
		node->next->prev = new_node;
	}

	node->next = new_node;

	return new_node;
}

int free_list(List *nodes) {
	if(nodes == NULL) {
		return RET_OK;
	}

	List *nodes_to_free = nodes;
	List *tmp_node;

	while(nodes_to_free != NULL) {
		tmp_node = nodes_to_free->next;
		free(nodes_to_free);
		nodes_to_free = tmp_node;
	}

	return RET_OK;
}

