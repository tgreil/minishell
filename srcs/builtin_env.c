/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:47:14 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/18 15:23:33 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**builtin_env_create_tmp(t_cmd *cmd)
{
	char	**env;
	int		i;

	i = 2;
	env = NULL;
	while (cmd->arg[i] && ft_strchr(cmd->arg[i], '=') && cmd->arg[i][0] != '=')
		i++;
	return (env);
}

int			builtin_env_tmp(t_cmd *cmd)
{
	char		**env_tmp;
	t_env_list	*tmp;

	(void)cmd;
	tmp = NULL;
	env_tmp = NULL;
//	if (tmp = env_init(cmd->&arg[2]))
//		return (EXIT_ERROR);
	env_print(tmp);
	return (1);
}

int			builtin_env(t_cmd *cmd, t_env_list *env)
{
	int			i;
	t_env_list	*list;

	i = 0;
	list = env;
	(void)cmd; //a retirer
	if (cmd->arg[1])
	{
		if (!ft_strcmp(cmd->arg[1], "-i"))
			return (builtin_env_tmp(cmd));
		else
		{
			//msg d'erreur, commande inconnu, usage?
			return (EXIT_SUCCESS);
		}

	}
	while (list)
	{
		ft_printf("%s\n", list->data);
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
