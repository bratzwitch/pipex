/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:17 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:46 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_infile(char *infile)
{
	int	fdin;

	if (ft_strncmp(infile, "here_doc", 9))
	{
		fdin = open(infile, O_RDONLY);
		if (fdin < 0)
		{
			perror(infile);
			return (-1);
		}
		return (fdin);
	}
	return (-2);
}

int	open_outfile(char *heredoc, char *outfile)
{
	int	flags;
	int	fdout;

	flags = O_WRONLY | O_CREAT;
	if (!ft_strncmp(heredoc, "here_doc", 9))
		flags = flags | O_APPEND;
	else
		flags = flags | O_TRUNC;
	fdout = open(outfile, flags, 0644);
	if (fdout < 0)
	{
		perror(outfile);
		return (-1);
	}
	return (fdout);
}
