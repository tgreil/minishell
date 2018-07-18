/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgreil <tgreil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 17:39:13 by tgreil            #+#    #+#             */
/*   Updated: 2018/07/18 19:29:47 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cmd_parser_replace_size(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	return (i);
}

char		*cmd_parser_replace_var(char *s, t_env_list *env, int i)
{
	char	*replace;
	char	*new;
	int		var_len;
	int		my_i;

	my_i = 0;
	var_len = cmd_parser_replace_size(s + i + 1);
	if (!(new = malloc(var_len + 1)))
		return (NULL);
	ft_strncpy(new, s + i + 1, var_len);
	replace = env_get(env, new);
	free(new);
	if (!(new = malloc(ft_strlen(s) + (replace ? ft_strlen(replace) : 0))))
		return (NULL);
	ft_strncpy(new, s, i);
	if (replace)
		ft_strcat(new, replace);
	ft_strcat(new, s + i + var_len + 1);
	free(s);
	return (new);
}

char		*cmd_parser_replace(char *s, t_env_list *env)
{
	char	*new;
	int		i;

	i = 0;
	ft_printf("REPLACE: |{red}%s{eoc}|\n", s);
	while (s[i])
	{
		if (s[i] == '$' && (!i || s[i - 1] != '\\'))
		{
			new = cmd_parser_replace_var(s, env, i);
			return (cmd_parser_replace(new, env));
		}
		i++;
	}
	return (s);
}
