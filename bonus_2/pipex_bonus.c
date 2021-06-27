/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/26 22:33:11 by inyang           ###   ########.fr       */
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

void	make_stdin(char **av)
{
	int	pipefd[2];

	printf("this is first\n");
	in_to_stdin(av[1]);
	printf("in?\n");
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	run_cmd(av[2]);
}

int	multi_pipe(int ac, char **av, t_cmd *m_pipe)
{
	int		fd[2];
	pid_t	pid;
	int		pipe_cnt;
	int		i;
	int		status;

	pipe_cnt = (ac - 4);
	fd_init(pipe_cnt, m_pipe);
	if ((pipe(m_pipe->m_fd[0])) == -1)
		error_msg("pipe error\n");
	pid = fork();
	if (pid < 0)
		error_msg("pid error\n");
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("real fin\n");
	}
	else if (pid == 0)
	{
		i = -1;
		while (++i < pipe_cnt)
		{
			// waitpid(pid, &status, 0);
			// if(WIFEXITED(status))
			// 	printf("last pang!\n");
			// printf("[%d] ", i);
			pipe(fd);
			pid = fork();
			if (pid <= 0)
				break;
		}
		printf("check i %d\n", i);
		if (pid == 0 && i == 0)
			make_stdin(av);
		else if (pid == 0)
		{
			printf("check %d\n", i);
			close(fd[1]);
			pipe(fd);
			dup2(fd[0], 0);
			dup2(fd[1], 1);
			close(fd[0]);
			run_cmd(av[i + 2]);
		}
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if(WIFEXITED(status))
				printf("last pang!\n");
		}
		printf("real finn\n");
	}
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
