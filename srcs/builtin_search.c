/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:32:36 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/21 17:46:34 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_search(t_cmd *cmd, t_env_list **env)
{
	if (!cmd || !cmd->arg[0])
		return (-1);
	else if (!ft_strcmp(cmd->arg[0], "echo"))
		return (builtin_echo(cmd, env));
	else if (!ft_strcmp(cmd->arg[0], "cd"))
		return (builtin_cd(cmd, env));
	else if (!ft_strcmp(cmd->arg[0], "setenv"))
		return (builtin_setenv(cmd, env));
	else if (!ft_strcmp(cmd->arg[0], "unsetenv"))
		return (builtin_unsetenv(cmd, env));
	else if (!ft_strcmp(cmd->arg[0], "env"))
		return (builtin_env(cmd, env));
	return (exec_access(cmd, env));
}
