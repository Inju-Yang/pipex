/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/24 05:00:33 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc_cmd(char **av)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		tmp_to_stdout();
		dup2(pipefd[0], 0);
		close_pipe(pipefd);
		run_cmd(av[4]);
	}
	else if (pid == 0)
	{
		tmp_to_stdin();
		dup2(pipefd[1], 1);
		close_pipe(pipefd);
		run_cmd(av[3]);
	}
	return (0);
}

int	here_doc(int ac, char **av)
{
	char	*line;
	int		value;
	int		strlen;

	if (ac != 5)
		return (0);
	value = 1;
	write(1, "here_doc> ", 10);
	while ((value = px_gnl(&line)) > 0)
	{
		strlen = ft_strlen(line);
		if (px_strcmp(line, av[2]) == 0)
			break ;
		dup2(0, 1);
		make_tmp();
		write(1, line, strlen);
		write(1, "\n", 1);
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
		wait(NULL);
	else if (pid == 0)
	{
		// if (ac > 5)
		// 	multi_pipe(ac, av);
		if (px_strcmp(av[1], "here_doc") == 0)
		{
			here_doc(ac, av);
			here_doc_cmd(av);
		}
	}
	// // if (ac > 5)
	// // 	multi_pipe(ac, av);
	// if (px_strcmp(av[1], "here_doc") == 0)
	// 	here
	return (0);
}
