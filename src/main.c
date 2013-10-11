#include "common.h"

int main() {

	int ch, i;
	struct termios term;
	struct termios term2;

	tcgetattr( STDIN_FILENO, &term );

	printf("ATTRIBUTES 0\n");
	printf("%d\n", term.c_iflag);
	printf("%d\n", term.c_oflag);
	printf("%d\n", term.c_cflag);
	printf("%d\n", term.c_lflag);

	term.c_lflag &= ~( ICANON | ECHO );
	
	printf("ATTRIBUTES 1\n");
	printf("%d\n", term.c_iflag);
	printf("%d\n", term.c_oflag);
	printf("%d\n", term.c_cflag);
	printf("%d\n", term.c_lflag);


	//tcsetattr( STDIN_FILENO, TCSANOW, &term );

	printf("ATTRIBUTES 2\n");
	printf("%d\n", term.c_iflag);
	printf("%d\n", term.c_oflag);
	printf("%d\n", term.c_cflag);
	printf("%d\n", term.c_lflag);


	/*for (i = 0; i < 4; i++) {
		puts("enter arrow");
		ch = getchar() & 0xFF;
		ch += getchar() & 0xFF;
		ch += getchar() & 0xFF;
		//printf("%c | %d\n", ch, ch); 
		printf("%d\n", ch); 
	}*/

	

	return 0;
}
