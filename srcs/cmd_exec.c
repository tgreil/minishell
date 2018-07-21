/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t <t@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:50:40 by t                 #+#    #+#             */
/*   Updated: 2018/07/21 16:06:34 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		cmd_parser_split_end(char **arg, char *line, int *i)
{
	char	c;

	c = line[*i];
	if (arg)
		line[*i] = '\0';
	if (c)
		(*i)++;
	return (c);
}

int			cmd_parser_split_increment(char *line, int *i)
{
	while (line[*i] && line[*i] != ' ' &&
		line[*i] != '\t' && line[*i] != ';')
	{
		if (line[*i] == '"' && *i > 0 && line[(*i - 1)] != '\\')
		{
			(*i)++;
			while (line[*i] && (line[*i] != '"'
							|| (line[*i] == '"' && line[(*i - 1)] != '\\')))
				(*i)++;
		}
		(*i)++;
	}
	return (EXIT_SUCCESS);
}

int			cmd_parser_split(char **arg, char *line, int *i)
{
	int		nb_words;
	char	c;

	c = 42;
	nb_words = 0;
	while (c != '\0' && c != ';')
	{
		while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
			(*i)++;
		if (line[*i] && line[*i] != ';' && arg)
			arg[nb_words] = line + *i;
		if (line[*i] && line[*i] != ';')
			nb_words++;
		cmd_parser_split_increment(line, i);
		c = cmd_parser_split_end(arg, line, i);
	}
	return (nb_words);
}

t_cmd		*cmd_parser(char *line)
{
	t_cmd	*new;
	int		size;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(t_cmd))))
		return (NULL);
	new->next = NULL;
	new->arg = NULL;
	if ((size = cmd_parser_split(NULL, line, &i)) <= 0)
		return (new);
	if (!(new->arg = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	new->arg[size] = NULL;
	i = 0;
	cmd_parser_split(new->arg, line, &i);
	while (size-- > 0)
		if (!(new->arg[size] = ft_strdup(new->arg[size])))
			return (NULL);
	if (line[i])
		if (!(new->next = cmd_parser(line + i)))
			return (NULL);
	return (new);
}

int			cmd_exec(t_env_list **env, char *line)
{
	t_cmd	*cmd;
	t_cmd	*next;
	int		i;

	if (!(cmd = cmd_parser(line)))
		return (EXIT_ERROR);
	while (cmd)
	{
		i = 0;
		cmd_parser_interpret(cmd, *env);
		if (cmd->arg)
			builtin_search(cmd, env);
		while (cmd->arg[i])
			free(cmd->arg[i++]);
		free(cmd->arg);
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
	return (EXIT_SUCCESS);
}
