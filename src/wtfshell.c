#include "wtfshell.h"

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

Value get_char() {
	Value value;
	value.character = getchar();
	value.integer = value.character & 0xFF;

	return value;
}

// GO LEFT
// GO RIGHT

int run_shell() {
	List *tmp_buffer = NULL;
	Value tmp_value;
	int ascii_code;
	int offset = 0;
	bool escape_pressed = false;

	for (;;) {
		tmp_value = get_char();
		ascii_code = tmp_value.integer + offset;
		offset = 0;

		if(ascii_code >= BEGIN_NORMAL && ascii_code <= END_NORMAL) {
			if(escape_pressed && ascii_code == OPEN_S_B) {
				offset = ESC + OPEN_S_B;
			} else {
			tmp_buffer = push_elem(tmp_buffer, tmp_value);
				if(tmp_buffer->next == NULL && tmp_buffer->prev == NULL) {
					buffer = tmp_buffer;	// We keep the head.
				}
				print_buffer(tmp_buffer);
			}
		} else {
			switch(ascii_code) {
				case RIGHT_A_K: // RIGHT			// CALL FUNCTION!!! KEEP TRACK OF CURSOR POS
					if(tmp_buffer != NULL && tmp_buffer->next != NULL) {
						printf("\033[1C");
						tmp_buffer = tmp_buffer->next;
					}
					break;
				case LEFT_A_K:// LEFT
					if(tmp_buffer != NULL && tmp_buffer->prev != NULL) {
						printf("\033[1D");
						tmp_buffer = tmp_buffer->prev;
					}
					break;
				default: break;
			} 
		}
		
		if(ascii_code == ESC) {
			escape_pressed = true;
		} else {
			escape_pressed = false;
		}
	}

	return RET_OK;
}

