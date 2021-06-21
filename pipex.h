/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:32:26 by inyang            #+#    #+#             */
/*   Updated: 2021/06/21 17:20:27 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./libft/libft.h"

# define CHILD	0

typedef struct	s_cmd
{
	const char	*cmd[5];
	char *const	*argv;
	char *const	*envp;
}				t_cmd;

int				main(int ac, char **av);
int				pipex(int ac, char **av);

int				redirect_in(const char *file);
void			connect_pipe(int pipefd[2], int io);
int				redirect_out(const char *file);
void			run_cmd(char *cmd);


#endif
