#include	<stdio.h> 
#include	<unistd.h> 
#include	<stdlib.h>
#include	<sys/types.h> 

int	main(void) 
{
	char *cmd[2];
	int	pid, status, i;
	pid_t	wpid;

	cmd[0] = "cat";
	cmd[1] = NULL;

	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		printf("real fin\n");
	}
	else if (pid == 0)
	{
		for (i = 0; i < 10; i++)	
		{
			pid = fork();
			if (pid == 0 || pid == -1)
				break;
		}
		printf("i meoim? %d\n", i);
		if (pid == -1)
		{	
			printf("fork error\n");
			exit(1);	
		}
		else if (pid == 0 && i == 5)
		{
			printf("순서 확인\n");
			execve("/bin/cat", cmd, 0);
		}
		else if (pid == 0) // code that each child process will run	
		{
			printf("child no. %d\n", i);	  
			exit(0);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if(WIFEXITED(status))
				printf("parent here\n");
		}
	}
} 

