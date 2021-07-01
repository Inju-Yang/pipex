/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:39:20 by inyang            #+#    #+#             */
/*   Updated: 2021/06/29 22:15:31 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	error_msg(cmd_src.argv[0]);
}

void		close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int			out_to_stdout(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		error_msg("out file error\n");
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int			in_to_stdin(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		error_msg("out file error\n");
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}
