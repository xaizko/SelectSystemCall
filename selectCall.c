#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

/* timed read line */
char *trl(int timeout) {
    static char buf[512]; //static means that it will be saved in memory
    fd_set rfds;
    struct timeval tv;
    int retval;

    FD_ZERO(&rfds); 
    FD_SET(0, &rfds);

    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    retval = select(1, &rfds, 0, 0, &tv);
    if (retval && FD_ISSET(0, &rfds)) {
	memset(buf, 0, 512);
	retval = read(0, buf, 511);
	if (retval < 1) {
	    return 0;
	}
	retval--;
	buf[retval] = 0;
	return buf;
    } else {
	return 0;
    }
}

int main() {
    char *name;
    printf("Enter your name, quick!:\n");
    name = trl(3);
    if (name) {
	printf("Hello %s\n", name);
    } else {
	printf("too slow!\n");
    }
    return 0;
}
