/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:59:13 by piliegeo          #+#    #+#             */
/*   Updated: 2018/08/03 15:15:01 by piliegeo         ###   ########.fr       */
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

	var_len = cmd_parser_replace_size(s + i + 1);
	if (!(new = malloc(var_len + 1)))
		return (NULL);
	new = ft_strncpy(new, s + i + 1, var_len);
	new[var_len] = 0;
	replace = env_get(env, new);
	free(new);
	if (!(new = malloc(ft_strlen(s) + (replace ? ft_strlen(replace) : 0))))
		return (NULL);
	ft_strncpy(new, s, i);
	new[i] = 0;
	if (replace)
		ft_strcat(new, replace);
	ft_strcat(new, s + i + var_len + 1);
	free(s);
	return (new);
}

char		*cmd_parser_replace_home(char *s, t_env_list *env)
{
	char	*replace;
	char	*new;

	if (!(replace = env_get(env, "HOME")))
		return (s);
	if (!(new = malloc(ft_strlen(s) + ft_strlen(replace))))
		return (NULL);
	new = ft_strcpy(new, replace);
	new = ft_strcat(new, s + 1);
	free(s);
	return (new);
}

char		*cmd_parser_replace(char *s, t_env_list *env)
{
	char	*new;
	int		i;

	i = 0;
	if (s[i] == '~')
		if (!(s = cmd_parser_replace_home(s, env)))
			return (NULL);
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
