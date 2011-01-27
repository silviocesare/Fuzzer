#include <stdio.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	while (argc--) {
		printf("%s\n", *argv++);
	}
	raise(SIGSEGV);
	return 0;
}
