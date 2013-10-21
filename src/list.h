#include "common.h"

typedef union Value Value;

union Value {
	int integer;
	char character;
};

typedef struct ListElem ListElem;
typedef struct List List;

struct ListElem {
	Value value;
	ListElem *prev;
	ListElem *next;
};

struct List {
	ListElem *head;
	ListElem *current;
	ListElem *queue;
	size_t position;
	size_t size;
};


void init_list(List *);
ListElem* new_elem(Value);
int push_elem(List *, Value);
int move_begin_list(List *);
int move_end_list(List *);
int backward_list(List *);
int forward_list(List *);
int delete_elem(List *);
int free_list(List *);

