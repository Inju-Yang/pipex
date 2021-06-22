/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/22 22:34:21 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	pipex(char **av)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		redirect_out(av[4]);
		connect_pipe(pipefd, STDIN_FILENO);
		run_cmd(av[3]);
	}
	else if (pid == 0)
	{
		redirect_in(av[1]);
		connect_pipe(pipefd, STDOUT_FILENO);
		run_cmd(av[3]);
	}
	return (0);
}

void	fork_process(char **av)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("Pid Error here\n");
	if (pid > 0)// 부모프로세서가 됐다면 이 프로세서는 기다리기
		wait(&pid);
	else if (pid == 0)//자식프로세서가 됐다면 이 프로세서 실행
		cmd_1(av);
}

int	main(int ac, char **av)
{
	int		value;
	char	*line;

	ac = 5;
	if (px_strcmp(av[1], "here_doc") == 0)
	{
		while ((value = px_gnl(&line)) > 0)
		{
			if (px_strcmp(line, av[2]) == 0)
				cmd_2()
			fork_process(av);
		}
	}
}
