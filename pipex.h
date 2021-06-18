/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inyang <inyang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:32:26 by inyang            #+#    #+#             */
/*   Updated: 2021/06/18 16:15:29 by inyang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define CHILD	0

# define FILE_1	av[1]
# define FILE_2	av[4]
# define CMD_1	av[2]
# define CMD_2	av[3]

typedef struct		s_cmd
{
	const char		*cmd;
	char * const	*argv;
	char * const	*envp;
}					t_cmd;

int main(int ac, char **av, char **envp);

#endif