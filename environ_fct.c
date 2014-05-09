/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 16:49:22 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/24 20:12:10 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char	**copy_env(char **environ)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = NULL;
	while (environ && environ[i])
		i++;
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		ft_error("copy_env: memory allocation failed");
	while (environ && environ[j])
	{
		env[j] = ft_strdup(environ[j]);
		j++;
	}
	env[j] = NULL;
	return (env);
}

char	**copy_path(char **environ)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (environ && environ[i] && ft_strncmp(environ[i], "PATH=", 5))
		i++;
	if (environ && environ[i])
		path = ft_strsplit(environ[i] + 5, ':');
	if (!path)
		ft_error("copy_path: variable PATH not found");
	return (path);
}
