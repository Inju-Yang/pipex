/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/24 04:05:34 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(char **av)
{
	int		pipefd[2];
	pid_t	pid;
	char	*line;
	int		value;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		// make_tmp();
		// dup2(pipefd[0], 0);
		// close_pipe(pipefd);
		// run_cmd(av[3]);
	}
	else if (pid == 0)
	{
		value = 1;
		close(pipefd[0]);
		while ((value = px_gnl(&line)) > 0)
		{
			if (px_strcmp(line, av[2]) == 0)
				break ;
			printf("%s", line);
		}
		dup2(0, 1);
		make_tmp();
		// close_pipe(pipefd);
		// execve("/bin/echo", NULL, NULL);
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
	// pid_t	pid;

	ac = 5;
	if (px_strcmp(av[1], "here_doc") == 0)
		here_doc(av);
	return (0);
}
