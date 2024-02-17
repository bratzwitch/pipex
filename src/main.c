/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:26 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:41 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	err;

	err = 0;
	if (ac >= 5)
		err += pipex(ac, av, envp);
	else
		err += error("Not enough arguments\n");
	if (err)
		return (1);
	else
		return (0);
}

int	error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}
