/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:13 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:49 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	dup_fd_io(int fdout, int fdin);
static void	command_not_found_clear_print(char *cmd, void *cmdargs,
				void *env_path);

int	exec_command(char *cmd, char **envp, int fdout, int fdin)
{
	int		i;
	t_env	env;
	char	*pathname;
	char	**cmdargs;

	env = parse_env_path(envp);
	i = -2;
	cmdargs = ft_split(cmd, ' ');
	if (!cmdargs || !env.env_path || dup_fd_io(fdout, fdin))
		return (1);
	while (++i == -1 || env.env_path[i])
	{
		if (i == -1)
			pathname = cmd;
		else
			pathname = ft_strjoin(env.env_path[i], cmdargs[0]);
		if (!pathname)
			return (1);
		execve(pathname, cmdargs, env.envp);
		if (i != -1)
			free(pathname);
	}
	command_not_found_clear_print(cmd, cmdargs, env.env_path);
	return (0);
}

static int	dup_fd_io(int fdout, int fdin)
{
	if (fdout >= 0)
	{
		if (dup2(fdout, 1) == -1)
			return (1);
	}
	if (dup2(fdin, 0) == -1)
		return (1);
	return (0);
}

static void	command_not_found_clear_print(char *cmd, void *cmdargs,
		void *env_path)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found...\n", 2);
	free_word_list(cmdargs);
	free_word_list(env_path);
}
