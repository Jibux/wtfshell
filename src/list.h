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
ListElem* push_elem(List *, Value);
// Backward
// Forward
// FreeElem or delete

int free_list(ListElem *);

