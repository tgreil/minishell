/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:32:36 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/18 14:47:56 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin builtin[6]=
{
	{"cd", 1},
	{"echo", 2},
	{"env", 3},
	{"setenv", 4},
	{"ensetenv", 5},
	{0, 0}
};

void	builtin_initiate_tab(int (**pf)(t_cmd*, t_env_list*))
{
//	pf[0] = &builtin_cd;
	pf[1] = &builtin_echo;
	pf[2] = &builtin_env;
/*	pf[3] = &builtin_setenv;
	pf[4] = &builtin_unsetenv;
*/	pf[5] = &exec_access;
}

int		builtin_search(t_cmd *cmd, t_env_list *env)
{
	int		i;
	int		(*pf[6])(t_cmd*, t_env_list*);

	i = 0;
	builtin_initiate_tab(pf);
	while (builtin[i].name && ft_strcmp(cmd->arg[0], builtin[i].name))
		i++;
	return (pf[i](cmd, env));
}
