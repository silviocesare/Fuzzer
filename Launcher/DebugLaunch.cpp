#include <sys/ptrace.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include <cassert>

static void
Usage()
{
	fprintf(stderr, "Usage: foo [-t timeout] filename args...\n");
	exit(1);
}

static volatile pid_t globalPid;

static void
timeoutHandler(int sig)
{
	kill(globalPid, SIGKILL);
	exit(0);
}

int
main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	int ch;
	int ret;
	int status;
	int timeout = 0;
	char s[1024];

	while ((ch = getopt(argc, argv, "t:p:")) != EOF) {
		switch (ch) {
		case 'p':
			snprintf(s, sizeof(s), "LD_PRELOAD=%s", optarg);
			putenv(s);
			break;

		case 't':
			timeout = atoi(optarg);
			break;

		default:
			Usage();
		}
	}
	argc -= optind;
	argv += optind;
	if (argc < 1) {
		Usage();
	}

	pid = fork();
	switch (pid) {
	case  0:
		ret = ptrace(PTRACE_TRACEME, 0, 0, 0);
		assert(ret == 0);
		execv(argv[0], &argv[1]);
		fprintf(stderr, "execve error\n");
		exit(1);
	case -1:
		fprintf(stderr, "fork error\n");
		exit(1);
	default:
		break;
	}
	ret = waitpid(pid, &status, 0);
	assert(ret == pid);
	assert(WIFSTOPPED(status));
	ret = ptrace(PTRACE_CONT, pid, 0, 0);
	assert(ret == 0);
	if (timeout != 0) {
		globalPid = pid;
		signal(SIGALRM, timeoutHandler);
		alarm(timeout);
	}
	while (1) {
		unsigned int sig;

		ret = waitpid(pid, &status, 0);
		assert(ret == pid);
		if (WIFEXITED(status)) {
			break;
		}
		if (WIFSTOPPED(status)) {
			sig = WSTOPSIG(status);
			if (sig == SIGSEGV) {
				fprintf(stderr, "++++ segv\n");
				exit(100);
			}
		}
		ret = ptrace(PTRACE_CONT, pid, 0, sig);
		assert(ret == 0);
	}
	fprintf(stderr, "++++ ok\n");
	exit(0);
}
