#include "common.h"
#include "list.h"

// GLOBAL VARIABLES
tcflag_t backupflag;
struct termios term;
List *buffer;

void print_error(char *);
void sig_handler(int);
int init_shell();
int quit_shell();
int print_buffer(List *);

