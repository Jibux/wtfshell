#include "functions.h"


// TODO
// Chained list for buffer?
// What can we do with the WTF global variables?

int main(int argc, char* argv[]) {

	int ch;
	char cha;


	if(init_shell() == RET_ERROR) {
		print_error("Cannot init!");
		return RET_ERROR;
	}
	
	//int fd;
	//struct winsize win;
	// forkpty(master, name, &term, &win);
	/*pid_t pid = forkpty(&fd, NULL, &term, NULL);
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
	printf("master fd: %d\n", fd);*/

	int arrow1 = 0, print_char = 0;

	//for (i = 0; i < 4; i++) {
	while (1) {
		//puts("enter arrow");
		cha = getchar();
		ch = cha & 0xFF;
		
		print_char = 1;

		if(arrow1 == 1 && ch == 91) {
			ch += getchar() & 0xFF;
			ch += 27;
			print_char = 0;
			if(ch == 185) {
				printf("\033[1C");
			} else if(ch == 186) {
				printf("\033[1D");
			}
		}
		arrow1 = 0;
		if(ch == 27) {
			arrow1 = 1;
			print_char = 0;
		}

		if(print_char == 1) {
			printf("%c", cha); 
		}
		
		/*printf("%d\n", ch); 
		ch += getchar() & 0xFF;
		printf("%d\n", ch); 
		ch += getchar() & 0xFF;
		//printf("%c | %d\n", ch, ch); 
		printf("%d\n", ch); */
	}

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

	if(quit_shell() == RET_ERROR) {
		print_error("Error while exiting shell");
	}

	return 0;
}

/*
 *
 
  struct termios oldt;
  struct termios newt;
  tcgetattr(STDIN_FILENO, &oldt); store old settings 
newt = oldt; copy old settings to new settings 
newt.c_lflag &= ~(ICANON | ECHO); make one change to old settings in new settings 
tcsetattr(STDIN_FILENO, TCSANOW, &newt); apply the new settings immediatly 
ch = getchar(); standard getchar call 
tcsetattr(STDIN_FILENO, TCSANOW, &oldt); reapply the old settings*/ 
