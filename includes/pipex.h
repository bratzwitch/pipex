/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:46:09 by dfarhi            #+#    #+#             */
/*   Updated: 2024/02/17 14:33:06 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../lib_ft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char	**envp;
	char	**env_path;
}			t_env;
int			pipe_test(char *cmd, t_env env, char *infile);
t_env		parse_env_path(char **envp);
void		free_word_list(char **env_path);
int			open_infile(char *infile);
int			open_outfile(char *heredoc, char *outfile);
int			pipex(int ac, char **av, char **envp);
int			heredoc(char *delimiter, int fdout);
int			pipex_heredoc(char *delimiter);
int			exec_command(char *cmd, char **envp, int fdout, int fdin);
int			error(char *str);
int			check_file_permissions(int ac, char **av);
int			create_pipe(int *fd);
void		print_fd_read(int fd);

t_list		*ft_lstget_index(t_list *lst, int index);

#endif
