/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 16:34:40 by inyang            #+#    #+#             */
/*   Updated: 2021/06/29 21:29:37 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	delete_tmp(void)
{
	char *for_rm[3];

	for_rm[0] = "rm";
	for_rm[1] = "tmp";
	for_rm[2] = NULL;
	execve("/bin/rm", for_rm, 0);
}

int		here_doc_cmd(char **av)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		tmp_to_stdout(av[5]);
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

int		make_tmp(void)
{
	int	fd;

	fd = open("tmp", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		error_msg("tmp file error\n");
		return (-1);
	}
	return (fd);
}

int		here_doc(int ac, char **av)
{
	char	*line;
	int		value;
	int		strlen;
	char	*prompt;
	int		fd;

	if (ac != 6)
		return (0);
	value = 1;
	prompt = "pipe heredoc> ";
	write(1, prompt, ft_strlen(prompt));
	fd = make_tmp();
	while ((value = px_gnl(&line)) > 0)
	{
		strlen = ft_strlen(line);
		if (px_strcmp(line, av[2]) == 0)
		{
			close(fd);
			return (0);
		}
		write(fd, line, strlen);
		write(fd, "\n", 1);
		write(1, prompt, ft_strlen(prompt));
	}
	return (0);
}
