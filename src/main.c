#include "common.h"

int main(int argc, char* argv[]) {

	int ch, i, fd;

	struct termios term;
	struct winsize win;
	// forkpty(master, name, &term, &win);
	
	pid_t pid = forkpty(&fd, NULL, &term, NULL);
	if (pid == -1) {
		perror("forkpty");
		return 1;
	} else if (pid == 0) {
		if (execlp("/bin/sh", "sh", (void*)0) == -1) {
			perror("execlp");
		}
		fprintf(stderr, "program exited.\n");
		return 1;
	}
	printf("Child process: %d\n", pid);
	printf("master fd: %d\n", fd);

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



	
	/*const char* cmd = "ls -l /\n";
	if (write(fd, cmd, strlen(cmd)) == -1) {
		perror("write");
		return 1;
	}

	char buf[255];
	int nread;
	while ((nread = read(fd, buf, 254)) > 0) {
		int i;
		for (i = 0; i < nread; i++) {
			putchar(buf[i]);
		}
	}
	printf("Done\n");*/




	return 0;
}
