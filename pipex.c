/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/21 17:05:16 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int ac, char **av)
{
	int		pipefd[2];
	pid_t	pid;

	if (ac != 5)
		return (0);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		redirect_out(av[4]);
		connect_pipe(pipefd, STDIN_FILENO);
		run_cmd(av[3]);
	}
	else if (pid == CHILD)
	{
		redirect_in(av[1]);
		connect_pipe(pipefd, STDOUT_FILENO);
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
		wait(&pid);
	else if (pid == CHILD)//자식프로세서가 됐다면 이 프로세서 실행
		pipex(ac, av);
	return (0);
}
