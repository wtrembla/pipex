/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/22 13:56:17 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/24 18:54:49 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_env		*init_env(char **environ)
{
	static t_env	*env = NULL;

	if (!env)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env))))
			ft_error("init_env: memory allocation failed");
		env->env = copy_env(environ);
		env->path = copy_path(environ);
	}
	return (env);
}

void		del_env(void)
{
	t_env	*env;

	env = init_env(NULL);
	if (env)
	{
		del_av(env->env);
		del_av(env->path);
		free(env);
		env = NULL;
	}
}

int			main(int ac, char **av, char **environ)
{
	if (ac != 5)
		ft_error("usage: ./pipex infile cmd1 cmd2 outfile");
	av++;
	init_env(environ);
	pipex(av, env);
	return (0);
}
