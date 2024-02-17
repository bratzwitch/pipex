/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:31 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:40 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	create_pipe(int *fd)
{
	if (pipe((int *)fd))
	{
		perror("Pipe: ");
		return (1);
	}
	return (0);
}

void	print_fd_read(int fd)
{
	int		n;
	char	*buff[16];

	n = 15;
	while (n >= 15)
	{
		ft_bzero(buff, 16);
		n = read(fd, buff, 15);
		ft_printf("%s", buff);
	}
}

t_list	*ft_lstget_index(t_list *lst, int index)
{
	int	i;

	if (index < 0)
		return (NULL);
	i = -1;
	while (lst)
	{
		if (++i == index)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
