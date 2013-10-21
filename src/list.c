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
	
	list->size++;
	list->position++;

	return RET_OK;
}

int move_begin_list(List *list) {
	list->current = list->head;
	return RET_OK;
}

int move_end_list(List *list) {
	list->current = list->queue;
	return RET_OK;
}

int backward_list(List *list) {
	if(list->current == NULL) {
		list->current = list->head;
		return RET_OK;
	}

	if(list->current->prev != NULL) {
		list->current = list->current->prev;
	}
	
	return RET_OK;
}

int forward_list(List *list) {
	if(list->current == NULL) {
		list->current = list->head;
		return RET_OK;
	}

	if(list->current->next != NULL) {
		list->current = list->current->next;
	}
	
	return RET_OK;
}

int delete_elem(List *list) {
	if(list->current == NULL) {
		list->current = list->queue;
	}

	if(list->current->prev == NULL) {
		list->head = list->current->next;
	} else {
		list->current->prev->next = list->current->next;
	}

	if(list->current->next == NULL) {
		list->queue = list->current->prev;
	} else {
		list->current->next->prev = list->current->prev;
	}

	free(list->current);
	list->current = NULL;

	return RET_OK;
}

int free_list(List *list) {
	while(list->queue != NULL) {
		delete_elem(list);
	}

	return RET_OK;
}

