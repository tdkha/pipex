# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <err.h>
#include <string.h>
int  main(void)
{
	pid_t pid;

	pid = fork();
	
	if (pid == 0)
	{
		printf("Hello world\n");
	}
	else
	{
		printf("Hello wolf\n");
	}
	waitpid(pid, NULL, 0);
}