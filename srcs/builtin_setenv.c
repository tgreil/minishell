/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:59:17 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/19 15:49:43 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t		builtin_setenv_strlen_envname(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

t_env_list	*builtin_setenv_new_env(char *new_env, t_env_list *env)
{
	t_env_list		*new;
	t_env_list		*list;

	list = env;
	if (!(new = ft_memalloc(sizeof(t_env_list))))
		return (NULL);
	if (!(new->data = ft_strdup(new_env)))
		return (NULL);
	while (list->next)
		list = list->next;
	list->next = new;
	return (new);
}

int			builtin_setenv(t_cmd *cmd, t_env_list **env)
{
	t_env_list		*lst;
	int				i;
	size_t			len;

	i = 1;
	while (cmd->arg[i] && ft_strchr(cmd->arg[i], '=') && cmd->arg[i][0] != '=')
	{
		lst = *env;
		len = builtin_setenv_strlen_envname(cmd->arg[i]);
		while (lst && ft_strncmp(cmd->arg[i], lst->data, len))
			lst = lst->next;
		if (lst)
		{
			free(lst->data);
			if (!(lst->data = ft_strdup(cmd->arg[i])))
				return (EXIT_ERROR);
		}
		else
		{
			if (!(builtin_setenv_new_env(cmd->arg[i], *env)))
				return (EXIT_ERROR);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
