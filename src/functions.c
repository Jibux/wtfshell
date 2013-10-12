#include "functions.h"

void print_error(char *string) {
	fprintf(stderr, "%s\n", string);	
}

void sig_handler(int signal) {
	if (signal == SIGINT) {
		printf("exit\n");
		
		if(quit_shell() == RET_ERROR) {
			print_error("Error while exiting shell");
		}

		exit(0);
	}
}

int init_shell() {

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		fprintf(stderr, "\nCan't catch SIGINT\n");
	}

	tcgetattr( STDIN_FILENO, &term );
	// Backup the flag to reset it properly when exiting the program.
	backupflag = term.c_lflag;

	/*
	 * Get rid off canonical mode and echo mode (~ICANON and ~ECHO)
	 * ICANON: print new line
	 * ECHO: print entered key
	 */
	term.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	return RET_OK;
}

int quit_shell() {
	// Restore flag
	term.c_lflag = backupflag;
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	// Free buffer!

	return RET_OK;
}

