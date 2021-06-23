/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:32:26 by inyang            #+#    #+#             */
/*   Updated: 2021/06/24 02:25:55 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct	s_cmd
{
	const char	*cmd[5];
	char *const	*argv;
	char *const	*envp;
}				t_cmd;

int				main(int ac, char **av);
int				pipex(char **av);

int				in_to_stdin(const char *file);
int				out_to_stdout(const char *file);
void			run_cmd(char *cmd);
void			close_pipe(int pipefd[2]);
int			make_tmp();
int				px_strcmp(char *str1, char *str2);

int				px_gnl(char **line);
char			*px_strjoin(char *s1, char *s2);
int				px_strlen(char *s);

#endif
