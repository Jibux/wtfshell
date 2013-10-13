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

	backupflag = term.c_lflag;	// Backup the flag to reset it properly when exiting the program.

	/*
	 * Get rid off canonical mode and echo mode (~ICANON and ~ECHO)
	 * ICANON: print new line
	 * ECHO: print entered key
	 */
	term.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	buffer = NULL;

	return RET_OK;
}

int quit_shell() {
	// Restore flag
	term.c_lflag = backupflag;
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	printf("\n");
	print_buffer(buffer);
	printf("\n");

	free_list(buffer);

	return RET_OK;
}

int print_buffer(List *buffer_to_print) {
	List *tmp_buffer;
	
	// Do IT DIFFERENTLY WITH GENERIC FORWARD AND BACKWARD ANS KEEP TRACKINg OF CURSOR POS
	printf("\033[s");

	while(buffer_to_print != NULL) {
		tmp_buffer = buffer_to_print->next;
		printf("%c", buffer_to_print->value.character);
		buffer_to_print = tmp_buffer;
	}

	printf("\033[u");
	printf("\033[1C");

	return RET_OK;
}

