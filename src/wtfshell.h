#include "common.h"
#include "list.h"
#include "ascii.h"
#include "command.h"

// CONSTANTS
#define CURSOR_DIR_LEFT 1
#define CURSOR_DIR_RIGHT 2

// GLOBAL VARIABLES
tcflag_t backupflag;
struct termios term;
List *buffer;

void print_error(const char *, ...);
void sig_handler(int);
int init_shell();
int quit_shell();
int free_buffer();
int print_buffer(List *);
Value get_char();
int move_cusor(List **, const short);
int run_shell();
int handle_cmd();

