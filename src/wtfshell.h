#include "common.h"
#include "list.h"
#include "ascii.h"

// GLOBAL VARIABLES
tcflag_t backupflag;
struct termios term;
List *buffer;

void print_error(char *);
void sig_handler(int);
int init_shell();
int quit_shell();
int print_buffer(List *);
Value get_char();
int run_shell();

