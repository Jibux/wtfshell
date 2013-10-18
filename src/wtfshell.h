#include "common.h"
#include "list.h"
#include "ascii.h"
#include "command.h"

// CONSTANTS
#define CURSOR_DIR_LEFT 1
#define CURSOR_DIR_RIGHT 2
#define CURSOR_DIR_BEGIN 3
#define CURSOR_DIR_END 4

// GLOBAL VARIABLES
tcflag_t backupflag;
struct termios term;
ListElem *buffer;

void sig_handler(int);
int init_shell();
void quit_shell();
int free_buffer();
int print_buffer(ListElem *);
Value get_char();
int move_cusor(ListElem **, const short);
int run_shell();
int handle_cmd();

