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

int push_elem(List *list, Value value) {
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
		return RET_OK;
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
	list->current = new_node;
	
	list->size++;
	list->position++;

	return RET_OK;
}

int move_begin_list(List *list) {
	list->current = NULL;
	list->position = 0;
	return RET_OK;
}

int move_head_list(List *list) {
	list->current = list->head;
	list->position = 1;
	return RET_OK;
}

int move_end_list(List *list) {
	list->current = list->queue;
	list->position = list->size;
	return RET_OK;
}

int backward_list(List *list) {
	if(list->current == NULL) {
		//move_begin_list(list);
		return RET_OK;
	} else {
		list->current = list->current->prev;
		list->position--;
	}
	
	return RET_OK;
}

int forward_list(List *list) {
	if(list->current == NULL) {
		move_head_list(list);
		return RET_OK;
	}

	if(list->current->next != NULL) {
		list->current = list->current->next;
		list->position++;
	}

	return RET_OK;
}

int delete_elem(List *list) {
	ListElem *next_current_node, *node_to_delete;
	if(list->queue == NULL) {
		return RET_OK;
	}

	if(list->current == NULL) {
		//move_end_list(list);
		return RET_OK;
	}

	node_to_delete = list->current;
	next_current_node = node_to_delete->prev;

	if(next_current_node == NULL) {
		list->head = node_to_delete->next;
	} else {
		next_current_node->next = node_to_delete->next;
	}

	if(node_to_delete->next == NULL) {
		list->queue = next_current_node;
	} else {
		node_to_delete->next->prev = next_current_node;
	}

	list->current = next_current_node;
	free(node_to_delete);
	list->size--;
	list->position--;

	return RET_OK;
}

int free_list(List *list) {
	while(list->queue != NULL) {
		delete_elem(list);
	}

	return RET_OK;
}

