#include "common.h"

typedef union Value Value;

union Value {
	int integer;
	char character;
};

typedef struct List List;

struct List {
	Value value;
	List *prev;
	List *next;
};

List* new_elem(Value);
List* push_elem(List*, Value);

int free_list(List *);

