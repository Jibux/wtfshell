#include "wtfshell.h"


// TODO
// Chained list for buffer?
// What can we do with the WTF global variables?

int main(int argc, char* argv[]) {

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

	if(init_shell() == RET_ERROR) {
		print_error("Cannot init!");
		return RET_ERROR;
	}

	if(run_shell() == RET_ERROR) {
		print_error("Cannot run shell!");
		return RET_ERROR;
	}
	
	quit_shell();

	return RET_OK;
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
