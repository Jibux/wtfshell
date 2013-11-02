#include "common.h"
#include "list.h"
#include "ascii.h"
#include "command.h"

// CONSTANTS
#define CURSOR_DIR_LEFT 1
#define CURSOR_DIR_RIGHT 2
#define CURSOR_DIR_BEGIN 3
#define CURSOR_DIR_END 4

#define EXPECTATIONS_SIZE 9
#define EXPECTATIONS_MAX_LENGTH 5

int EXPECTATIONS[EXPECTATIONS_SIZE][EXPECTATIONS_MAX_LENGTH];

// GLOBAL VARIABLES
tcflag_t backupflag;
struct termios term;
List *buffer;


void sig_handler(int);
int copy_in_2d_array(int [EXPECTATIONS_SIZE][EXPECTATIONS_MAX_LENGTH], int *, int);
int init_expectations();
int init_shell();
void quit_shell();
int free_buffer_content();
int free_buffer();
int print_buffer(bool);
Value get_char();
int forward_buffer();
int backward_buffer();
int move_cusor(const short);
int delete_from_buffer(bool);
int analyse_expectations(int);
int run_shell();
int handle_cmd();

