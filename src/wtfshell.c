#include "wtfshell.h"

void sig_handler(int signal) {
	if (signal == SIGINT) {
		quit_shell();
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

	init_list(buffer);

	return RET_OK;
}

void quit_shell() {
	// Restore flag
	term.c_lflag = backupflag;
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	printf("\n");
	print_buffer(buffer);
	printf("\n");

	free_buffer();

	printf("exit\n");

	exit(0);
}

int free_buffer() {
	free_list(buffer);

	return RET_OK;
}

int print_buffer() {
	if(buffer->current == NULL) {
		return RET_OK;
	}

	// DO IT DIFFERENTLY WITH GENERIC FORWARD AND BACKWARD ANS KEEP TRACKING OF CURSOR POS
	printf("\033[s");

	do {
		printf("%c", buffer->current->value.character);
		forward_list(buffer);
	} while(buffer->current->next != NULL);

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

int move_cusor(const short direction) {
	switch(direction) {
		case CURSOR_DIR_LEFT:
			if(buffer->current != NULL) {
				printf("\033[1D");
				backward_list(buffer);
			}
			break;
		case CURSOR_DIR_RIGHT:
			if(buffer->current != NULL) {
				printf("\033[1C");
				forward_list(buffer);
			}
			break;
		case CURSOR_DIR_BEGIN:
			printf("\r");
			move_begin_list(buffer);
			break;
		case CURSOR_DIR_END:
			printf("\r");
			move_begin_list(buffer);
			print_buffer();
			break;
		default: break;
	}
	
	return RET_OK;
}

int run_shell() {
	Value tmp_value;
	int ascii_code = -1;
	int offset = 0;
	bool escape_pressed = false;

	for (;;) {
		tmp_value = get_char();
		ascii_code = tmp_value.integer + offset;
		offset = 0;

		if(ascii_code >= BEGIN_NORMAL && ascii_code <= END_NORMAL) {
			if(escape_pressed) {
				if(tmp_value.integer == OPEN_S_B || tmp_value.integer == O_KEY) {
					offset = ESC + tmp_value.integer;
				}
			} else {
				push_elem(buffer, tmp_value);
				print_buffer();
			}
		} else {
			switch(ascii_code) {
				case EOT:
					quit_shell();
					break;
				case RIGHT_A_K:
					move_cusor(CURSOR_DIR_RIGHT);
					break;
				case LEFT_A_K:
					move_cusor(CURSOR_DIR_LEFT);
					break;
				case BEGIN:
					move_cusor(CURSOR_DIR_BEGIN);
					break;
				case END:
					move_cusor(CURSOR_DIR_END);
					break;
				case ENTER:
					if(handle_cmd() == RET_ERROR) {
						print_error("Error while executing command!");
					}
					break;
				default:
					//printf("%d => %c\n", ascii_code, tmp_value.character);
					break;
			} 
		}
		
		if(ascii_code == ESC) {
			escape_pressed = true;
		} else {
			escape_pressed = false;
		}

		ascii_code = -1;
	}

	return RET_OK;
}

int handle_cmd() {
	printf("\n");
	printf("CMD: ");
	move_begin_list(buffer);
	print_buffer();
	printf("\n");

	free_buffer();

	execute_cmd();

	return RET_OK;
}

