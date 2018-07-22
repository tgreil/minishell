/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:52:31 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/22 15:54:39 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_unsetenv_usage(t_cmd *cmd, int i)
{
	if (!cmd->arg[1])
		ft_printf("!2!usage: unsetenv [name]\n", cmd->arg[1]);
	else
		ft_printf("unsetenv: %s doesn't exist\n", cmd->arg[i]);
	return (EXIT_SUCCESS);
}

void		builtin_unsetenv_remove(t_env_list *current, t_env_list *prev,
		t_env_list **env)
{
	*env = (!prev ? current->next : *env);
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

	i = 0;
	if (!cmd->arg[1])
		return (builtin_unsetenv_usage(cmd, 0));
	while (cmd->arg[++i])
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
			builtin_unsetenv_remove(lst, prev, env);
		else
			return (builtin_unsetenv_usage(cmd, i));
	}
	return (EXIT_SUCCESS);
}
