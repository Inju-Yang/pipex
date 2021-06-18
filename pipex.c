/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/18 16:26:55 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1_len;
	unsigned int	s2_len;
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (!(s1) || !(s2))
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	j = -1;
	if (!(str = malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	return (str);
}

static size_t	ft_cnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			cnt++;
		}
	}
	return (cnt);
}

static int		ft_n_malloc(char **all, size_t k, size_t cnt)
{
	if (!(all[k] = malloc(cnt + 1)))
	{
		while (k > 0)
		{
			k--;
			free(all[k]);
		}
		free(all);
		return (1);
	}
	return (0);
}

static size_t	ft_index(size_t *i, char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (s[*i] != c && s[*i])
	{
		(*i)++;
		cnt++;
	}
	return (cnt);
}

static int		ft_fill(char const *s, char c, char **all)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	cnt;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		cnt = ft_index(&i, s, c);
		if (ft_n_malloc(all, k, cnt))
			return (1);
		l = 0;
		j = i - cnt;
		while (j < i)
			all[k][l++] = (char)s[j++];
		all[k++][l] = '\0';
	}
	return (0);
}

char			**ft_split(char const *s, char c)
{
	size_t	len;
	char	**all;

	if (!s)
		return (NULL);
	len = ft_cnt(s, c);
	if (!(all = malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	if (ft_fill(s, c, all))
		return (NULL);
	all[len] = NULL;
	return (all);
}

static void	cmd_init(const char *cmd, t_cmd *strt)
{
	char	**chunk;

	chunk = ft_split(cmd, ' ');
	strt->cmd[0] = ft_strjoin("/bin/", chunk[0]);
	strt->cmd[1] = ft_strjoin("/usr/local/bin/", chunk[0]);
	strt->cmd[2] = ft_strjoin("/usr/bin/", chunk[0]);
	strt->cmd[3] = ft_strjoin("/usr/sbin/", chunk[0]);
	strt->cmd[4] = ft_strjoin("/sbin/", chunk[0]);
	strt->argv = (char *const *)chunk;
	strt->argv[5] = NULL;
}

static void	run_cmd(const char *cmd, t_cmd *cmd_arg)
{
	int i;

	i = 0;
	cmd_init(cmd, cmd_arg);
	while(i < 5)
		execve(&cmd_arg->cmd[i++], cmd_arg->argv, cmd_arg->envp);
	perror(cmd_arg->argv[0]);
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
	close(pipefd[0]);
	close(pipefd[1]);
}

int	redirect_in(const char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file); //perror를 통해 stderr인 
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	t_cmd	cmd_arg;

	if (ac != 5)
		return (0);
	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid > 0)
	{
		redirect_out(FILE_2);
		connect_pipe(pipefd, STDIN_FILENO);
		run_cmd(CMD_2, &cmd_arg);
	}
	else if (pid == CHILD)
	{
		redirect_in(FILE_1);
		connect_pipe(pipefd, STDOUT_FILENO);
		run_cmd(CMD_1, &cmd_arg);
	}
	return 0;
}