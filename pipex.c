/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/20 18:35:35 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cmd_init(char *argv, t_cmd *strt)
{
	char	**chunk;

	chunk = ft_split(argv, ' ');
	strt->cmd[0] = ft_strjoin("/bin/", chunk[0]);
	strt->cmd[1] = ft_strjoin("/usr/local/bin/", chunk[0]);
	strt->cmd[2] = ft_strjoin("/usr/bin/", chunk[0]);
	strt->cmd[3] = ft_strjoin("/usr/sbin/", chunk[0]);
	strt->cmd[4] = ft_strjoin("/sbin/", chunk[0]);
	strt->argv = (char *const *)chunk;
	strt->envp = NULL;
}

static void	run_cmd(char *cmd)
{
	int		i;
	t_cmd	cmd_arg;

	i = 0;
	cmd_init(cmd, &cmd_arg);
	while(i < 5)
		execve(cmd_arg.cmd[i++], cmd_arg.argv, cmd_arg.envp);
	perror(cmd_arg.argv[0]);
}

int	redirect_out(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static void	connect_pipe(int pipefd[2], int io)
{
	dup2(pipefd[io], io);
	close(pipefd[0]); //pipefd[0] == sth -> STDIN
	close(pipefd[1]); //pipefd[1] == sth -> STDOUT
}

int	redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int pipex(int ac, char **av)
{
	int		pipefd[2];
	pid_t	pid;

	if (ac != 5)
		return (0);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		redirect_out(FILE_2);
		connect_pipe(pipefd, STDIN_FILENO);
		run_cmd(CMD_2);
	}
	else if (pid == CHILD)
	{
		redirect_in(FILE_1);
		connect_pipe(pipefd, STDOUT_FILENO);
		run_cmd(CMD_1);
	}
	return 0;
}

int main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 5)
		return (0);
	pid = fork();
	if (pid < 0)
		perror("Pid Error here\n");
	if (pid > 0)
		wait(&pid);
	else if (pid == CHILD)
		pipex(ac, av);
	return 0;
}
