#include "wtfshell.h"

void sig_handler(int signal) {
	if (signal == SIGINT) {
		quit_shell();
	}
}

int copy_in_2d_array(int array1[EXPECTATIONS_SIZE][EXPECTATIONS_MAX_LENGTH], int *array2, int index) {
	int j;

	for(j = 0; j < EXPECTATIONS_MAX_LENGTH; j++) {
		array1[index][j] = array2[j];
	}

	return RET_OK;
}

int init_expectations() {
	int ascii0[] = {ESC,	OPEN_S_B,	D_KEY,	LEFT_A_K,	NO_CMD};
	int ascii1[] = {ESC,	OPEN_S_B,	C_KEY,	RIGHT_A_K,	NO_CMD};
	int ascii2[] = {ESC,	OPEN_S_B,	NUM_3,	TILDE,		DEL_R};
	int ascii3[] = {ESC,	O_KEY,		H_KEY,	BEGIN,		NO_CMD};
	int ascii4[] = {ESC,	O_KEY,		F_KEY,	END,		NO_CMD};
	int ascii5[] = {DEL,	DEL_L,		NO_CMD,	NO_CMD,		NO_CMD};
	int ascii6[] = {ENTER,	ENTER_CMD,	NO_CMD,	NO_CMD,		NO_CMD};
	int ascii7[] = {EOT,	EOT_CMD,	NO_CMD,	NO_CMD,		NO_CMD};
	int ascii8[] = {NO_CMD,	NO_CMD,		NO_CMD,	NO_CMD,		NO_CMD};

	int i, j;

	for(i = 0; i < EXPECTATIONS_SIZE; i++) {
		for(j = 0; j < EXPECTATIONS_MAX_LENGTH; j++) {
			EXPECTATIONS[i][j] = NO_CMD;
		}
	}

	copy_in_2d_array(EXPECTATIONS, ascii0, 0);
	copy_in_2d_array(EXPECTATIONS, ascii1, 1);
	copy_in_2d_array(EXPECTATIONS, ascii2, 2);
	copy_in_2d_array(EXPECTATIONS, ascii3, 3);
	copy_in_2d_array(EXPECTATIONS, ascii4, 4);
	copy_in_2d_array(EXPECTATIONS, ascii5, 5);
	copy_in_2d_array(EXPECTATIONS, ascii6, 6);
	copy_in_2d_array(EXPECTATIONS, ascii7, 7);
	copy_in_2d_array(EXPECTATIONS, ascii8, 8);

	return RET_OK;
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

	List buffer_tmp;

	buffer = &buffer_tmp;
	buffer = (List*) malloc(sizeof(List));

	init_list(buffer);

	init_expectations();

	return RET_OK;
}

void quit_shell() {
	// Restore flag
	term.c_lflag = backupflag;
	tcsetattr( STDIN_FILENO, TCSANOW, &term );

	printf("\n");
	move_begin_list(buffer);
	print_buffer(false);
	printf("\n");

	free_buffer();

	printf("exit\n");

	exit(0);
}

int free_buffer_content() {
	free_list(buffer);
	return RET_OK;
}

int free_buffer() {
	free_buffer_content();
	free(buffer);
	return RET_OK;
}

int print_buffer(bool backup) {
	if(buffer->head == NULL) {
		return RET_OK;
	}
	
	int pos = buffer->position;
	ListElem *tmp = buffer->current;

	if(buffer->current == NULL) {
		move_head_list(buffer);
	}

	// DO IT DIFFERENTLY WITH GENERIC FORWARD AND BACKWARD ANS KEEP TRACKING OF CURSOR POS
	printf("\033[s");

	printf("%c", buffer->current->value.character);
	while(buffer->current->next != NULL) {
		forward_list(buffer);
		printf("%c", buffer->current->value.character);
	}

	if(backup) {
		buffer->current = tmp;
		buffer->position = pos;

		printf("\033[u");
		printf("\033[1C");
	}

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
			if(buffer->size != buffer->position) {
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
			print_buffer(false);
			move_end_list(buffer);
			break;
		default: break;
	}
	
	return RET_OK;
}

int delete_from_buffer(bool right) {
	if(right) {
		forward_list(buffer);
	} else {
		printf("\033[1D");
	}

	if(buffer->current == NULL) {
		return RET_OK;
	} else {
		printf("\033[K");
	}
	
	delete_elem(buffer);

	if(buffer->current == NULL) {
		print_buffer(true);
		printf("\033[1D");
		return RET_OK;
	}

	if(buffer->current->next != NULL) {
		forward_list(buffer);
		print_buffer(true);
		backward_list(buffer);
		printf("\033[1D");
	}

	return RET_OK;
}

/*int run_shell() {
	Value tmp_value;
	int ascii_code = -1;
	int offset = 0;
	bool escape_pressed = false;
	bool continue_esc = false;

	for (;;) {
		tmp_value = get_char();
		ascii_code = tmp_value.integer + offset;
		continue_esc = false;
		if(!escape_pressed) {
			offset = 0;
		} else {
			offset = offset + tmp_value.integer;
		}

		// TODO WORK WITH TREE EXPECTATION... ESC then OPEN_S_B then etc.
		
		if(ascii_code >= BEGIN_NORMAL && ascii_code <= END_NORMAL) {
				//if(tmp_value.integer == OPEN_S_B || tmp_value.integer == O_KEY) {
			//		offset = offset + tmp_value.integer;
				//}
			//} else {
			if(!escape_pressed) {
				push_elem(buffer, tmp_value);
				print_buffer(true);
			}
		} else {
			switch(ascii_code) {
				case EOT:
					quit_shell();
					break;
				case DEL_L:
					delete_from_buffer(false);
					break;
			//	case DEL_R:
			//		delete_from_buffer(true);
			//		break;
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
					continue_esc = true;
					//printf("%d => %c\n", ascii_code, tmp_value.character);
					break;
			} 
		}
		
		if(ascii_code == ESC) {
			escape_pressed = true;
			offset = ESC;
		} else if(!continue_esc) {
			escape_pressed = false;
		}

		ascii_code = -1;
	}

	return RET_OK;
}*/

int analyse_expectations(int ascii_code) {
	static int max_i = 0;
	static int max_j = 0;
	int i, j;

	j = max_j;

	for(i = max_i; i < EXPECTATIONS_SIZE; i++) {
		if(EXPECTATIONS[i][j] == ascii_code) {
			if(j > 0 && i > 0) {
				if(EXPECTATIONS[i-1][j-1] == EXPECTATIONS[i][j-1]) {
					max_j++;
					max_i = i;
				}
			} else {
				max_j++;
				max_i = i;
			}

			if(j+1 >= EXPECTATIONS_MAX_LENGTH) {
				max_i = 0;
				max_j = 0;
				return NO_CMD;
			} else if(EXPECTATIONS[i][j+1] < 0) {
				max_i = 0;
				max_j = 0;
				return EXPECTATIONS[i][j+1];
			}

			return WAIT_CMD;
		}
	}

	max_i = 0;
	max_j = 0;
	
	return NO_CMD;
}

int run_shell() {
	Value tmp_value;
	int ascii_code = -1;
	int cmd_code = -1;

	for (;;) {
		tmp_value = get_char();
		ascii_code = tmp_value.integer;

		// EXPECTATIONS
		cmd_code = analyse_expectations(ascii_code);

		//printf("%d %d\n",ascii_code, cmd_code);

		switch(cmd_code) {
			case EOT_CMD:
				quit_shell();
				break;
			case DEL_L:
				delete_from_buffer(false);
				break;
			case DEL_R:
				delete_from_buffer(true);
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
			case ENTER_CMD:
				if(handle_cmd() == RET_ERROR) {
					print_error("Error while executing command!");
				}
				break;
			case NO_CMD:
				push_elem(buffer, tmp_value);
				print_buffer(true);
				break;
			default:
				//printf("%d => %c\n", ascii_code, tmp_value.character);
				break;
		}
	}

	return RET_OK;
}

int handle_cmd() {
	printf("\n");
	printf("CMD: ");
	move_begin_list(buffer);
	print_buffer(false);
	printf("\n");

	free_buffer_content();

	execute_cmd();

	return RET_OK;
}

