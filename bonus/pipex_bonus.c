/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/28 21:47:14 by inyang           ###   ########.fr       */
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
	// i = -1;
	// while (++i < pipe_cnt)
	// 	m_pipe->m_fd = malloc(sizeof(int) * pipe_cnt);
	// i = -1;
	// while (++i < pipe_cnt)
	// 	m_pipe->pipe = malloc(sizeof(int) * 2);
}

void	make_stdout(int ac, char **av, t_cmd *m_pipe)
{
	printf("last point check\n");
	// printf("%d\n", i);
	// printf("%d\n", m_pipe->m_fd[i][0]);
	out_to_stdout(av[ac - 1]);
	dup2(m_pipe->new_pipe[0], 0);
	// close_pipe(m_pipe->old_pipe);
	close_pipe(m_pipe->new_pipe);
	run_cmd(av[ac - 2]);
}

void	make_stdin(char **av, t_cmd *m_pipe)
{
	// printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i][0], m_pipe->m_fd[i][1]);
	// printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i + 1][0], m_pipe->m_fd[i+1][1]);
	printf("is stdin start\n");
	in_to_stdin(av[1]);
	dup2(m_pipe->new_pipe[1], 1);
	close_pipe(m_pipe->old_pipe);
	close_pipe(m_pipe->new_pipe);
	// printf("%d %s\n",i,  av[2]);
	// pid = fork();
	// if (pid == 0)
	// 	middle_cmd(av, m_pipe);
	run_cmd(av[2]);
}

int	multi_pipe(int ac, char **av, t_cmd *m_pipe)
{
	// int		i;
	pid_t	pid;
	int		status;
	// int		used_pipe[2];
	// int		new_pipe[2];
	// int		cmd_count;

	m_pipe->cmd_count = ac - 3;
	// fd_init(cmd_count, m_pipe);
	// i = -1;
	// while (++i < cmd_count)
	// 	if (pipe(m_pipe->m_fd[i]) == -1)
	// 		error_msg("pipe_error\n");
	pipe(m_pipe->new_pipe);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);//2대가 5번 자식을
		if(!WIFEXITED(status))
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
	// printf("cmd_count: %d\n", m_pipe->cmd_count);
	if (m_pipe->cmd_count == 1)
		make_stdin(av, m_pipe);
	else
	{
		m_pipe->old_pipe[0] = m_pipe->new_pipe[0];
		m_pipe->old_pipe[1] = m_pipe->new_pipe[1];
		dup2(m_pipe->old_pipe[1], 1);
		close_pipe(m_pipe->old_pipe);
		pipe(m_pipe->new_pipe);
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (!WIFEXITED(status))
				exit(1);
			dup2(m_pipe->new_pipe[0], 0);
			close_pipe(m_pipe->new_pipe);
			run_cmd(av[m_pipe->cmd_count + 1]);
		}
		else if (pid == 0)
			make_child(m_pipe, av);
		else
			error_msg("pid error\n");
	}
}

		// else if (pid == 0)
		// {
		// 	printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i - 1][0], m_pipe->m_fd[i - 1][1]);
		// 	printf("pipefd[0] %d [1] %d\n", m_pipe->m_fd[i][0], m_pipe->m_fd[i][1]);
		// 	printf("???\n");
		// 	dup2(m_pipe->m_fd[i - 1][0], 0);
		// 	dup2(m_pipe->m_fd[i][1], 1);
		// 	close_pipe(m_pipe->old_pipe);
		// 	close_pipe(m_pipe->new_pipe);
		// 	run_cmd(av[i + 2]);
		// }
		// else if (pid > 0)
		// {
		// 	waitpid(pid, &status, 0);
		// 	if (WIFEXITED(status))
		// 		make_stdout(ac, av, m_pipe, i - 1, i);
		// }
		// if (pid < 0)
		// 	error_msg("pid error\n");

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
