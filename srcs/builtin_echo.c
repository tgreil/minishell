/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 14:35:04 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/19 15:48:48 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_echo(t_cmd *cmd, t_env_list **env)
{
	int i;

	(void)env;
	i = 1;
	while (cmd->arg[i])
	{
		ft_printf("%s", cmd->arg[i++]);
		if (cmd->arg[i])
			ft_printf(" ");
	}
	ft_printf("\n");
	return (EXIT_SUCCESS);
}
