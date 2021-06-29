/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/29 20:33:34 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_msg(char *str)
{
	perror(str);
	exit(1);
}

int		pipex(char **av)
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

int		main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 5)
		return (0);
	pid = fork();
	if (pid < 0)
		error_msg("Pid Error here\n");
	if (pid > 0)
		wait(NULL);
	else if (pid == 0)
		pipex(av);
	return (0);
}
