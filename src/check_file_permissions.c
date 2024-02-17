/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_permissions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:04 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:54 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	check_permission(char *file_name, int mode)
{
	if (access(file_name, mode))
	{
		ft_printf("%s: permission denied\n", file_name);
		return (1);
	}
	return (0);
}

int	check_file_permissions(int ac, char **av)
{
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		if (check_permission(av[5], W_OK))
			return (1);
	}
	else
	{
		if (check_permission(av[1], R_OK))
			return (1);
		if (check_permission(av[ac - 1], W_OK))
			return (1);
	}
	return (0);
}
