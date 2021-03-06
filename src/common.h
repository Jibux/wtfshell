#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pty.h>  /* for openpty and forkpty */ 
#include <utmp.h> /* for login_tty */
#include <signal.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <wchar.h>
#include <locale.h>
//#include <ncurses.h>


// DEFINE SOME CONSTANTS

#define RET_ERROR 1
#define RET_OK 0


void print_error(const char *, ...);

