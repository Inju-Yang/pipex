/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/25 21:06:01 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fd_init(int pipe_cnt, t_cmd *m_pipe)
{
	int i;
	i = -1;
	m_pipe->m_fd = malloc(sizeof(int *) * (pipe_cnt));
	while (++i < pipe_cnt)
		m_pipe->m_fd[i] = malloc(sizeof(int) * 2);
}

void	make_stdout(int ac, char **av, t_cmd *m_pipe, int i)
{
	close(m_pipe->m_fd[i + 1][0]);
	printf("this is last : %s\n", av[ac - 2]);
	out_to_stdout(av[ac - 1]);
	dup2(m_pipe->m_fd[i][0], 0);
	close(m_pipe->m_fd[i + 1][1]);
	run_cmd(av[ac - 2]);
}

void	make_stdin(char **av, t_cmd *m_pipe)
{
	printf("this is first\n");
	in_to_stdin(av[1]);
	dup2(m_pipe->m_fd[0][1], 1);
	close(m_pipe->m_fd[0][0]);
	run_cmd(av[2]);
}

int	multi_pipe(int ac, char **av, t_cmd *m_pipe)
{
	pid_t	pid[ac - 4];
	int		pipe_cnt;
	int		i;

	printf("???????\n");
	pipe_cnt = (ac - 4);
	fd_init(pipe_cnt, m_pipe);
	i = -1;
	while (++i < pipe_cnt)
	{
		printf("DLWP DLRJEH DKSEHLA?\n");
		// printf("sdfjsfjksdfkjsfd>> %d\n", (pipe(m_pipe->m_fd[i])));
		if ((pipe(m_pipe->m_fd[i])) == -1)
			error_msg("pipe error\n");
		pid[i] = fork();
	}
	printf("%d\n", i);
	i = -1;
	while (++i < pipe_cnt)
	{
		printf("this is i %d\n", i);
		if (pid[i] > 0)
		{
			wait(NULL);
			make_stdout(ac, av, m_pipe, i);
		}
		else if (pid[i] == 0)
			make_stdin(av, m_pipe);
		else
		{
			close(m_pipe->m_fd[i][1]);
			dup2(m_pipe->m_fd[i][0], 0);
			dup2(m_pipe->m_fd[i + 1][1], 1);
			close(m_pipe->m_fd[i + 1][0]);
			run_cmd(av[i + 2]);
		}
		printf("what can i do\n");
	}
	while (++i < pipe_cnt)
		
	printf("sejfalhio\n");
	return (0);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	t_cmd	m_fd;

	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		pid = fork();
		if (pid > 0)
			wait(NULL);
		else if (pid == 0)
		{
			if (px_strcmp(av[1], "here_doc") == 0)
				delete_tmp();
			else
				return (0);
		}
		else
			exit(0);
	}
	else if (pid == 0)
	{
		if (px_strcmp(av[1], "here_doc") == 0)
		{
			here_doc(ac, av);
			here_doc_cmd(av);
		}
		else
			multi_pipe(ac, av, &m_fd);
	}
	else
		perror("Pid Error here\n");
	return (0);
}
