/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_envmodifier.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:45:27 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/20 16:48:28 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd_create_env(t_env_list **env, char *envname, char *path)
{
	t_env_list	*new;
	t_env_list	*lst;

	lst = *env;
	if (!(new = ft_memalloc(sizeof(t_env_list))))
		return (EXIT_ERROR);
	if (!(new->data = ft_strjoin(envname, path)))
		return (EXIT_ERROR);
	if (!*env)
		*env = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	return (EXIT_SUCCESS);
}

int		builtin_cd_change_env(t_env_list **env, char *envname, char *path)
{
	t_env_list	*lst;
	size_t		len;

	lst = *env;
	len = builtin_setenv_strlen_envname(envname);
	while (lst && lst->data && ft_strncmp(envname, lst->data, len))
		lst = lst->next;
	if (lst)
	{
		free(lst->data);
		if (!(lst->data = ft_strjoin(envname, path)))
			return (EXIT_ERROR);
	}
	else
	{
		if (builtin_cd_create_env(env, envname, path) < 0)
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}
