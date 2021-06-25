/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:32:26 by inyang            #+#    #+#             */
/*   Updated: 2021/06/25 20:39:54 by inyang           ###   ########.fr       */
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
	int			**m_fd;
}				t_cmd;

int				main(int ac, char **av);
int				pipex(char **av);

int				here_doc(int ac, char **av);
int				here_doc_cmd(char **av);
void			delete_tmp();

int				tmp_to_stdin(void);
int				tmp_to_stdout(char *file);
void			run_cmd(char *cmd);
void			close_pipe(int pipefd[2]);
int				make_tmp();
int				px_strcmp(char *str1, char *str2);

int				px_gnl(char **line);
char			*px_strjoin(char *s1, char *s2);
int				px_strlen(char *s);

int			out_to_stdout(const char *file);
int			in_to_stdin(const char *file);
void	error_msg(char *str);
#endif
