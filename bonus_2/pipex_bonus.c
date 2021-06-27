/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/27 20:36:27 by inyang           ###   ########.fr       */
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
	i = -1;
	while (++i < pipe_cnt)
		m_pipe->m_fd = malloc(sizeof(int) * pipe_cnt);
}

void	make_stdout(int ac, char **av, t_cmd *m_pipe, int i)
{
	// printf("last point check\n");
	// printf("%d\n", m_pipe->m_fd[i][0]);
	out_to_stdout(av[ac - 1]);
	dup2(m_pipe->m_fd[i][0], 0);
	close(m_pipe->m_fd[i][1]);
	run_cmd(av[ac - 2]);
}

void	make_stdin(char **av, t_cmd *m_pipe, int i)
{
	// int	pipefd[2];

	printf("this is first\n");
	printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i][0], m_pipe->m_fd[i][1]);
	printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i +1][0], m_pipe->m_fd[i+1][1]);
	in_to_stdin(av[1]);
	// printf("in?\n");
	dup2(m_pipe->m_fd[i + 1][1], 1);
	close(m_pipe->m_fd[i][0]);
	run_cmd(av[2]);
}

int	multi_pipe(int ac, char **av, t_cmd *m_pipe)
{
	// int		m_pipe->fd[2];
	pid_t	pid;
	pid_t	first_pid;
	int		pipe_cnt;
	int		i;
	int		status;

	pipe_cnt = (ac - 3);
	fd_init(pipe_cnt, m_pipe);
	i = -1;
	while (++i < pipe_cnt)
		if (pipe(m_pipe->m_fd[i]) == -1)
			error_msg("pipe_error\n");
	pid = fork();
	if (pid < 0)
		error_msg("pid error\n");
	if (pid > 0)
	{
		wait(NULL);
	}
	else if (pid == 0)//2대
	{
		i = -1;
		while (++i < pipe_cnt)
		{
			printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i][0], m_pipe->m_fd[i][1]);
			// printf("sorega pid %d\n",	pid);
			pid = fork();
			printf("%d\n", pid);
			m_pipe->for_wait[i] = pid;//2대
			printf("siehafl\n");
			if (i == 0 && pid > 0)
				first_pid = pid;
			printf("first_pid %d, pid %d\n", first_pid, pid);
			if (pid <= 0)
				break;
			// waitpid(pid, &status, 0);//2대가 5번 자식을
			// if(WIFEXITED(status))
			// 	printf("parent waiting\n");
		}
		if (pid < 0)
			error_msg("pid error\n");
		// printf("check i %d\n", i);
		if (pid == 0 && i == 0)//3ㅡ대 1번
			make_stdin(av, m_pipe, i);
		else if (pid == 0)//3대 1번 이후
		{
			printf("check %d\n", i);
			close(m_pipe->m_fd[i][1]);
			// pipe(m_pipe->m_fd);
			printf("pipem_pipe->m_fd[0] %d [1] %d\n", m_pipe->m_fd[i][0], m_pipe->m_fd[i][1]);
			printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i +1][0], m_pipe->m_fd[i+1][1]);
			dup2(m_pipe->m_fd[i][0], 0);
			dup2(m_pipe->m_fd[i + 1][1], 1);
			close(m_pipe->m_fd[i][0]);
			run_cmd(av[i + 1]);
		}
		else if (pid > 0)
		{
			printf("aeihfl\n");
			i = 0;
			while (i++ < pipe_cnt)
			{
				waitpid(m_pipe->for_wait[i], &status, 0);
			}
		}
		printf("i value %d\n", i);
		make_stdout(ac, av, m_pipe, i - 1);
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
