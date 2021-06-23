/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/23 23:00:51 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(char **av)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		out_to_stdout(av[4]);
		dup2(pipefd[0], 0);
		close_pipe(pipefd);
		run_cmd(av[3]);
	}
	else if (pid == 0)
	{
		in_to_stdin(av[1]);
		dup2(pipefd[1], 1);
		close_pipe(pipefd);
		run_cmd(av[2]);
	}
	return (0);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 5)
		return (0);
	pid = fork();
	if (pid < 0)
		perror("Pid Error here\n");
	if (pid > 0)// 부모프로세서가 됐다면 이 프로세서는 기다리기
		wait(NULL);
		// printf("그게 지금 나이면 돼~\n");
	else if (pid == 0)//자식프로세서가 됐다면 이 프로세서 실행
		pipex(av);
	return (0);
}
