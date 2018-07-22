/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 19:14:27 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/22 11:39:14 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**forkator_create_env(t_env_list *env, char **tab_env, int i)
{
	t_env_list		*lst;

	lst = env;
	if (!(tab_env = ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL);
	tab_env[i] = 0;
	i = 0;
	while (lst && lst->data)
	{
		if (!(tab_env[i] = ft_strdup(lst->data)))
			return (NULL);
		lst = lst->next;
		i++;
	}
	return (tab_env);
}

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
	if (i > 0)
		tab_env = forkator_create_env(env, tab_env, i);
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
	if (tab_env)
		exec_free_paths(tab_env);
	return (EXIT_SUCCESS);
}
