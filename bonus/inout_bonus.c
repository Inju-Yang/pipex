/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:38:12 by inyang            #+#    #+#             */
/*   Updated: 2021/06/29 22:02:52 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int			tmp_to_stdout(char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		error_msg("tmp out file error\n");
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int			tmp_to_stdin(void)
{
	int fd;

	fd = open("tmp", O_RDONLY);
	if (fd < 0)
	{
		error_msg("tmp in file error\n");
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int			out_to_stdout(const char *file)
{
	int fd;

	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		error_msg("out file error");
		exit(1);
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
		error_msg("in file error\n");
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}
