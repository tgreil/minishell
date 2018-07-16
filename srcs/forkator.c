/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:14:27 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/15 20:18:03 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**forkator_env(t_env_list *env)
{
	char			**tab_env;
	t_env_list		*lst;
	int				i;

	i = 0;
	lst = env;
	tab_env = NULL;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	lst = env;
	if (i > 0)
	{
		if (!(tab_env = ft_memalloc(sizeof(char*) * (i + 1))))
			return (NULL);
		tab_env[i] = 0;
		i = 0;
		while (lst)
		{
			if (!(tab_env[i] = ft_strdup(lst->data)))
				return (NULL);
			lst = lst->next;
			i++;
		}
	}
	return (tab_env);
}

int			forkator(t_cmd *cmd, t_env_list *env, char *path)
{
	pid_t	father;
	int		ret;
	char	**tab_env;

	tab_env = forkator_env(env);
	if ((father = fork()) == -1)
		return (EXIT_ERROR);
	if (father > 0)
		wait(&father);
	else if (father == 0)
	{
		ret = execve(path, cmd->arg, tab_env);
		exit(ret);
	}
	exec_free_paths(tab_env);
	//env_struct->paths = ft_free_env_paths(env_struct->paths);
	return (EXIT_SUCCESS);
}

