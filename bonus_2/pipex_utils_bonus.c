/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:39:20 by inyang            #+#    #+#             */
/*   Updated: 2021/06/27 17:14:25 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_msg(char *str)
{
	perror(str);
	exit(1);
}

static void	find_cmd_path(char *cmd, t_cmd *cmd_src)
{
	char	**cmd_to_run;

	cmd_to_run = ft_split(cmd, ' ');
	cmd_src->cmd[0] = ft_strjoin("/bin/", cmd_to_run[0]);
	cmd_src->cmd[1] = ft_strjoin("/usr/local/bin/", cmd_to_run[0]);
	cmd_src->cmd[2] = ft_strjoin("/usr/bin/", cmd_to_run[0]);
	cmd_src->cmd[3] = ft_strjoin("/usr/sbin/", cmd_to_run[0]);
	cmd_src->cmd[4] = ft_strjoin("/sbin/", cmd_to_run[0]);
	cmd_src->argv = (char *const *)cmd_to_run;
	cmd_src->envp = NULL;
}

void		run_cmd(char *cmd)
{
	int		i;
	t_cmd	cmd_src;

	i = 0;
	find_cmd_path(cmd, &cmd_src);
	while (i < 5)
		execve(cmd_src.cmd[i++], cmd_src.argv, cmd_src.envp);
	perror(cmd_src.argv[0]);
	exit(1);
}

void		close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int			tmp_to_stdout(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, 1);
	close(fd); //close는 왜?
	return (0);
}

int			tmp_to_stdin()
{
	int fd;

	fd = open("tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("tmp file opened");
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int			out_to_stdout(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, 1);
	close(fd); //close는 왜?
	return (0);
}

int			in_to_stdin(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	// printf("fd %d\n",fd);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int		px_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (1);
		else
			i++;
	}
	if (str1[i] != '\0' || str2[i] != '\0')
		return (1);
	return (0);
}
