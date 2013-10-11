#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>

#include <sys/param.h>
#include <sys/ioctl.h>

#include <errno.h>
#include <string.h>
#include <pty.h>  /* for openpty and forkpty */ 
#include <utmp.h> /* for login_tty */

//#include <util.h>
