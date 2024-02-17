/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:35 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:37 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	exec_pipex(char **cmds, int cmdn, char **envp, int *fdin_out);
static int	next_cmd(char *cmd, char **envp, int fdout, int fdin);
static int	pid_list_add(t_list **pid_lst, int pid);
static void	wait_pids(void *content);

/*
int	pipe_test(char *cmd, t_env env, char *infile)
{
	int	fd[2];
	int	file_fd;
	int	fork_res;

	if (pipe((int *)fd))
	{
		perror("Pipe: ");
		return (1);
	}
	if (ft_strncmp(infile, "stdin", 6) == 0)
		file_fd = dup(0);
	else
		file_fd = open(infile, O_RDONLY);
	if (file_fd < 0)
	{
		perror(infile);
		return (1);
	}
	fork_res = fork();
	if (fork_res < 0)
	{
		perror("Fork: ");
		return (1);
	}
	else if (!fork_res)
	{
		exec_command(cmd, env, fd[1], file_fd);
		exit(0);
	}
	else
	{
		print_fd_read(fd[0]);
	}
	close(fd[0]);
	close(fd[1]);
	close(file_fd);
	return (0);
}
*/

int	pipex(int ac, char **av, char **envp)
{
	int	fdin_out[2];
	int	i;

	i = 1;
	fdin_out[1] = open_infile(av[1]);
	fdin_out[0] = open_outfile(av[1], av[ac - 1]);
	if (fdin_out[1] == -1 || fdin_out[0] == -1)
		return (1);
	else if (fdin_out[1] == -2)
	{
		fdin_out[1] = pipex_heredoc(av[2]);
		i++;
	}
	if (exec_pipex(&av[i + 1], ac - i - 2, envp, fdin_out))
		return (1);
	return (0);
}

static int	exec_pipex(char **cmds, int cmdn, char **envp, int *fdin_out)
{
	int		i;
	int		fdin;
	int		fdout;
	int		fd[2];
	t_list	*pid;

	pid = 0;
	i = -1;
	fdin = fdin_out[1];
	while (++i < cmdn)
	{
		if (i < cmdn - 1 && create_pipe(fd))
			return (1);
		if (i == cmdn - 1)
			fdout = fdin_out[0];
		else
			fdout = fd[1];
		if (pid_list_add(&pid, next_cmd(cmds[i], envp, fdout, fdin)))
			return (1);
		fdin = fd[0];
	}
	ft_lstiter(pid, wait_pids);
	ft_lstclear(&pid, free);
	return (0);
}

static void	wait_pids(void *content)
{
	waitpid(*(int *)content, NULL, 0);
}

static int	pid_list_add(t_list **pid_lst, int pid)
{
	int		*content;
	t_list	*new;

	content = ft_calloc(1, sizeof(int));
	if (!content)
		return (1);
	*content = pid;
	new = ft_lstnew(content);
	if (!new)
		return (1);
	if (!*pid_lst)
		*pid_lst = new;
	else
		ft_lstadd_back(pid_lst, new);
	return (0);
}

static int	next_cmd(char *cmd, char **envp, int fdout, int fdin)
{
	int	fork_res;

	fork_res = fork();
	if (fork_res < 0)
	{
		perror("Fork: ");
		return (-1);
	}
	else if (!fork_res)
	{
		exec_command(cmd, envp, fdout, fdin);
		exit(0);
	}
	close(fdin);
	close(fdout);
	return (fork_res);
}
