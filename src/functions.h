#include "common.h"

// GLOBAL VARIABLES
tcflag_t backupflag;
struct termios term;

void print_error(char *);
void sig_handler(int);
int init_shell();
int quit_shell();
