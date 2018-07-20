/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:52:31 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/20 13:15:57 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_unsetenv_remove(t_env_list *current, t_env_list *prev)
{
	if (prev)
		prev->next = current->next;
	free(current->data);
	free(current);
}

int			builtin_unsetenv(t_cmd *cmd, t_env_list **env)
{
	t_env_list		*lst;
	t_env_list		*prev;
	int				i;
	size_t			len;

	i = 1;
	while (cmd->arg[i])
	{
		lst = *env;
		prev = NULL;
		len = builtin_setenv_strlen_envname(cmd->arg[i]);
		while (lst && lst->data && ft_strncmp(cmd->arg[i], lst->data, len))
		{
			prev = lst;
			lst = lst->next;
		}
		if (lst && lst->data && !ft_strncmp(cmd->arg[i], lst->data, len))
		{
			if (!prev)
				*env = lst->next;
			builtin_unsetenv_remove(lst, prev);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
