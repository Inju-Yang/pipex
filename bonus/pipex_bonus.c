/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:30:32 by inyang            #+#    #+#             */
/*   Updated: 2021/06/29 22:11:13 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	which_bonus(int ac, char **av, t_cmd *m_fd)
{
	if (px_strcmp(av[1], "here_doc") == 0)
	{
		here_doc(ac, av);
		here_doc_cmd(av);
	}
	else
		multi_pipe(ac, av, m_fd);
}

int		main(int ac, char **av)
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
		which_bonus(ac, av, &m_fd);
	else
		error_msg("Pid Error here\n");
	return (0);
}
