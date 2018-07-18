/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:47:14 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/18 20:46:33 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_env_free(t_cmd *cmd, t_env_list *env_list, char **env_tab)
{
	t_env_list		*tmp;
	int				i;

	i = 0;
	free(cmd->arg);
	free(cmd);
	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->data);
		free(env_list);
		env_list = tmp;
	}
	while (env_tab[i])
		free(env_tab[i++]);
	free(env_tab);
}

t_cmd		*builtin_create_cmd_tmp(t_cmd *cmd)
{
	t_cmd		*new;
	int			i;
	int			j;

	i = 2;
	j = 0;
	if (!(new = ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	while (cmd->arg[i] && ft_strchr(cmd->arg[i], '=') && cmd->arg[i][0] != '=')
		i++;
	while (cmd->arg[i + j])
		j++;
	if (!(new->arg = ft_memalloc(sizeof(char*) * j + 1)))
		return (NULL);
	new->arg[j] = NULL;
	j = 0;
	while (cmd->arg[i + j])
	{
		new->arg[j] = cmd->arg[i + j];
		j++;
	}
	return (new);
}

char		**builtin_create_env_tmp(t_cmd *cmd)
{
	char	**env;
	int		i;
	int		j;

	i = 2;
	j = 0;
	env = NULL;
	while (cmd->arg[i] && ft_strchr(cmd->arg[i], '=') && cmd->arg[i][0] != '=')
		i++;
	if (!(env = ft_memalloc(sizeof(char*) * i - 1)))
		return (NULL);
	env[i - 1] = NULL;
	i = 2;
	while (cmd->arg[i] && ft_strchr(cmd->arg[i], '=') && cmd->arg[i][0] != '=')
	{
		if (!(env[j++] = ft_strdup(cmd->arg[i++])))
			return (NULL);
	}
	return (env);
}

int			builtin_env_launcher(t_cmd *cmd)
{
	char		**env_tmp;
	t_env_list	*env_list_tmp;
	t_cmd		*cmd_tmp;

	env_tmp = builtin_create_env_tmp(cmd);
	env_list_tmp = env_init(env_tmp);
	cmd_tmp = builtin_create_cmd_tmp(cmd);
	if (cmd_tmp->arg[0])
		builtin_search(cmd_tmp, env_list_tmp);
	builtin_env_free(cmd_tmp, env_list_tmp, env_tmp);
	return (EXIT_SUCCESS);
}

int			builtin_env(t_cmd *cmd, t_env_list *env)
{
	int			i;
	t_env_list	*list;

	i = 0;
	list = env;
	if (cmd->arg[1])
	{
		if (!ft_strcmp(cmd->arg[1], "-i"))
			return (builtin_env_launcher(cmd));
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
