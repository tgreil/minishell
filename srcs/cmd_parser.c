/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:59:05 by piliegeo          #+#    #+#             */
/*   Updated: 2018/08/03 14:59:07 by piliegeo         ###   ########.fr       */
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
		if (s[i + diff])
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
	while (cmd->arg[i])
	{
		s = cmd->arg[i];
		cmd_parser_interpret_quot(s);
		cmd_parser_echaper(s);
		if (!(cmd->arg[i] = cmd_parser_replace(s, env)))
			return (EXIT_ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}
