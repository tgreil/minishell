/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 15:31:13 by tgreil            #+#    #+#             */
/*   Updated: 2018/07/18 16:13:53 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cmd_parser_interpret_quot(char *s)
{
	int	diff;
	int	i;

	i = 0;
	diff = 0;
	while (s[i + diff])
	{
		while (s[i + diff] == '"' && (!(i + diff) || s[i + diff - 1] != '\\'))
			diff++;
		s[i] = s[i + diff];
		i++;
	}
	s[i] = '\0';
	return (EXIT_SUCCESS);
}

int		cmd_parser_echaper(char *s)
{
	int	diff;
	int	i;

	i = 0;
	diff = 0;
	while (s[i + diff])
	{
		if (s[i + diff] == '\\' && s[i + diff + 1] == '"')
			diff++;
		s[i] = s[i + diff];
		i++;
	}
	s[i] = '\0';
	return (EXIT_SUCCESS);
}

int		cmd_parser_interpret(t_cmd *cmd, t_env_list *env)
{
	char	*s;
	int		i;

	i = 0;
	env += 1;
	while (cmd->arg[i])
	{
		s = cmd->arg[i];
		cmd_parser_interpret_quot(s);
		cmd_parser_echaper(s);
		ft_printf("{red}%s\n{eoc}", s);
		i++;
	}
	return (EXIT_SUCCESS);
}