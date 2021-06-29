/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:55:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/29 22:04:26 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	clean_up_pipes(t_cmd *m_pipe)
{
	m_pipe->old_pipe[0] = m_pipe->new_pipe[0];
	m_pipe->old_pipe[1] = m_pipe->new_pipe[1];
	dup2(m_pipe->old_pipe[1], 1);
	close_pipe(m_pipe->old_pipe);
	pipe(m_pipe->new_pipe);
}

void	make_stdout(int ac, char **av, t_cmd *m_pipe)
{
	out_to_stdout(av[ac - 1]);
	dup2(m_pipe->new_pipe[0], 0);
	close_pipe(m_pipe->new_pipe);
	run_cmd(av[ac - 2]);
}

void	make_stdin(char **av, t_cmd *m_pipe)
{
	in_to_stdin(av[1]);
	dup2(m_pipe->new_pipe[1], 1);
	close_pipe(m_pipe->new_pipe);
	run_cmd(av[2]);
}

int		multi_pipe(int ac, char **av, t_cmd *m_pipe)
{
	pid_t	pid;
	int		status;

	m_pipe->cmd_count = ac - 3;
	pipe(m_pipe->new_pipe);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			error_msg("pid error\n");
		close_pipe(m_pipe->old_pipe);
		make_stdout(ac, av, m_pipe);
	}
	else if (pid == 0)
		make_child(m_pipe, av);
	else
		error_msg("pid error\n");
	return (0);
}

void	make_child(t_cmd *m_pipe, char **av)
{
	pid_t	pid;
	int		status;

	m_pipe->cmd_count--;
	if (m_pipe->cmd_count == 1)
		make_stdin(av, m_pipe);
	else
	{
		clean_up_pipes(m_pipe);
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status))
				exit(1);
			dup2(m_pipe->new_pipe[0], 0);
			close_pipe(m_pipe->old_pipe);
			close_pipe(m_pipe->new_pipe);
			run_cmd(av[m_pipe->cmd_count + 1]);
		}
		else if (pid == 0)
			make_child(m_pipe, av);
		else
			error_msg("pid error\n");
	}
}
