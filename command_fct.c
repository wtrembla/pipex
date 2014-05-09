/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 15:47:16 by wtrembla          #+#    #+#             */
/*   Updated: 2014/04/30 17:11:20 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		improper_command(int ret, char *command)
{
	if (ret == -1 && (!ft_strncmp(command, "./", 2)
					|| !ft_strncmp(command, "../", 3) || command[0] == '/'))
		ft_putjoin_fd("pipex: no such file or directory: ", command, 2);
	else if (ret == -1)
		ft_putjoin_fd("pipex: command not found: ", command, 2);
	else if (ret == -2)
		ft_putjoin_fd("pipex: permission denied: ", command, 2);
}

static char		*check_command(char *command)
{
	char	*tmp;
	int		i;
	int		ret;
	t_env	*env;

	ret = 0;
	env = init_env(NULL);
	tmp = NULL;
	if ((!ft_strncmp(command, "./", 2) || !ft_strncmp(command, "../", 3)
		|| command[0] == '/') && !(ret = check_path(command)))
		return (ft_strdup(command));
	else if (!ret)
	{
		i = -1;
		while (env->path[++i])
		{
			ft_strdel(&tmp);
			tmp = build_path(env->path[i], command);
			if (!(ret = check_path(tmp)))
				return (tmp);
		}
	}
	improper_command(ret, command);
	ft_strdel(&tmp);
	return (NULL);
}

void			command_proc(char *command, int fd_in, int fd_out)
{
	char	**av;
	char	*tmp;

	av = ft_strsplit(command, ' ');
	if (av && (tmp = check_command(av[0])))
	{
		ft_strdel(&av[0]);
		av[0] = tmp;
		if ((father = fork()) == -1)
		{
			del_av(av)
			ft_error("comand_proc: call system fork error");
		}
		if (father)
			wait(0);
		if (father)
		{
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			if (execve(av[0], av, init_env(NULL)->env) == -1)
				ft_errjoin("pipex: command not found: ", av[0]);
		}
	}
	del_av(av);
}
