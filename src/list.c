#include "list.h"

void init_list(List *list) {
	list->head = NULL;
	list->current = NULL;
	list->queue = NULL;
	list->size = 0;
	list->position = 0;
}

ListElem* new_elem(Value value) {

	ListElem *new_node = (ListElem*)malloc(sizeof(ListElem));
	new_node->value.integer = value.integer;
	new_node->value.character = value.character;
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;
}

ListElem* push_elem(List *list, Value value) {
	ListElem *new_node = new_elem(value);
	ListElem *node = list->current;
	
	if(node == NULL) {
		node = list->head;
		list->head = new_node;
		list->size++;
		list->current = new_node;
		list->position = 1;
		if(node != NULL) {
			node->prev = new_node;
			new_node->next = node;
		}
		if(list->queue == NULL) {
			// First element of the list
			list->queue = new_node;
		}
		return new_node;
	}

	if(node->next != NULL) {
		// Add in middle
		new_node->next = node->next;
		node->next->prev = new_node;
	} else {
		// New queue
		list->queue = new_node;
	}

	new_node->prev = node;
	node->next = new_node;
	
	list->size++;
	list->position++;

	return new_node;
}

int free_list(ListElem *nodes) {
	if(nodes == NULL) {
		return RET_OK;
	}

	ListElem *nodes_to_free = nodes;
	ListElem *tmp_node;

	while(nodes_to_free != NULL) {
		tmp_node = nodes_to_free->next;
		free(nodes_to_free);
		nodes_to_free = tmp_node;
	}

	return RET_OK;
}

