/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:21 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:44 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	str_add_to_list(t_list **lst, char *str);
static void	put_list_fd(t_list *lst, int fd);

int	pipex_heredoc(char *delimiter)
{
	int	fd[2];

	if (pipe((int *)fd))
	{
		perror("Pipe: ");
		return (-1);
	}
	if (heredoc(delimiter, fd[1]))
		return (-1);
	return (fd[0]);
}

int	heredoc(char *delimiter, int fdout)
{
	t_list	*lst;
	char	*str;

	lst = NULL;
	delimiter = ft_strjoin(delimiter, "\n");
	if (!delimiter)
		return (1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str)
			return (1);
		if (!ft_strncmp(str, delimiter, ft_strlen(str)))
			break ;
		else if (str_add_to_list(&lst, str))
			return (1);
	}
	free(str);
	put_list_fd(lst, fdout);
	close(fdout);
	ft_lstclear(&lst, free);
	free(delimiter);
	return (0);
}

static int	str_add_to_list(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew((void *)str);
	if (!new)
		return (1);
	if (!*lst)
		*lst = new;
	else
		ft_lstadd_back(lst, new);
	return (0);
}

static void	put_list_fd(t_list *lst, int fd)
{
	int		i;
	t_list	*item;

	i = 0;
	while (1)
	{
		item = ft_lstget_index(lst, i);
		if (!item)
			return ;
		ft_putstr_fd(item->content, fd);
		i++;
	}
}
