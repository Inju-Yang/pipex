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
		wait(NULL); //1ㄷㅐ가 2대를
		printf("real fin\n");
	}
	else if (pid == 0)
	{
		for (i = 0; i < 10; i++)	
		{
			printf("pid is %d\n", pid);
			pid = fork();
			if (pid == 0 || pid == -1)
				break;
			waitpid(pid, &status, 0);//2대가 5번 자식을
			if(WIFEXITED(status))
				printf("parent waiting\n");
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
			waitpid(pid, &status, 0);//2대가 마지막 자식을
			if(WIFEXITED(status))
				printf("parent here\n");
		}
	}
} 

