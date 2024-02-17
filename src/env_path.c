/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:32:08 by vmoroz            #+#    #+#             */
/*   Updated: 2024/02/17 14:32:51 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**parse_env_path_add_slash(char **env_path);

t_env	parse_env_path(char **envp)
{
	int		i;
	char	**env_path;
	t_env	env;

	env.envp = envp;
	env.env_path = 0;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) == envp[i])
		{
			env_path = ft_split(&envp[i][5], ':');
			if (!env_path)
				return (env);
			env.env_path = parse_env_path_add_slash(env_path);
			return (env);
		}
	}
	return (env);
}

static char	**parse_env_path_add_slash(char **env_path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env_path[++i])
	{
		tmp = env_path[i];
		env_path[i] = ft_strjoin(tmp, "/");
		free(tmp);
	}
	return (env_path);
}

void	free_word_list(char **env_path)
{
	int	i;

	i = -1;
	while (env_path[++i])
		free(env_path[i]);
	free(env_path);
}
