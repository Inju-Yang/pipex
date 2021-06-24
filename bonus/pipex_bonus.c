/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/24 18:20:38 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"



int	multi_pipe(int ac, char **av)
{
	pid_t	pid;
	int		pipefd[2];
	int		pipefd2[2];
	int		i;
	// char	buf[2];
	// int		readlen;

	i = ac;
	if (pipe(pipefd) == -1)
		return (0);
	close(pipefd[1]);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		if (pipe(pipefd2) == -1)
			printf("error here\n");

		pid = fork();
		printf("new fork here\n");
		if (pid > 0)
		{
			printf("cmd 3 part\n");
			wait(NULL);
			printf("cmd 3 middle\n");
			out_to_stdout(av[5]);
			dup2(pipefd2[0], 0);
			close(pipefd2[1]);
//			close_pipe(pipefd2);
			run_cmd(av[4]);
		}
		else if (pid == 0)
		{
			printf("cmd 2 part\n");
			printf("pipefd[0] : %d, pipefd[1] : %d\n", pipefd[0], pipefd[1]);
			dup2(pipefd[0], 0);
//			close_pipe(pipefd);
			dup2(pipefd2[1], 1);
			close(pipefd2[0]);
//			close_pipe(pipefd2[1]);
			printf("cmd 2 part end\n");
			run_cmd(av[3]);
		}
	}
	else if (pid == 0)
	{
		printf("cmd 1 part\n");
		printf("pipefd[0] : %d, pipefd[1] : %d\n", pipefd[0], pipefd[1]);
		in_to_stdin(av[1]);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
//		close_pipe(pipefd);
		printf("cmd 1 part end\n");
		run_cmd(av[2]);
	}
	return (0);
}
// void	fork_process(char **av)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		perror("Pid Error here\n");
// 	if (pid > 0)// 부모프로세서가 됐다면 이 프로세서는 기다리기
// 		wait(&pid);
// 	else if (pid == 0)//자식프로세서가 됐다면 이 프로세서 실행
// 		here_doc(av);
// }

int	main(int ac, char **av)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Pid Error here\n");
	if (pid > 0)
	{
		wait(NULL);
		pid = fork();
		if (pid < 0)
			exit(0);
		if (pid > 0)
			wait(NULL);
		else if (pid == 0)
			delete_tmp();
	}
	else if (pid == 0)
	{
		if (ac > 5)
			multi_pipe(ac, av);
		else if (px_strcmp(av[1], "here_doc") == 0)
		{
			here_doc(ac, av);
			here_doc_cmd(av);
		}
		else
			multi_pipe(ac, av);
	}
	return (0);
}
