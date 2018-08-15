/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:59:20 by piliegeo          #+#    #+#             */
/*   Updated: 2018/08/03 15:57:36 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list		*env_shlvl(t_env_list *env, char *data)
{
	int		nb;
	char	*nb_tmp;
	int		i;

	i = 0;
	nb = ft_atoi(&data[6]) + 1;
	if (!(nb_tmp = ft_itoa(nb)))
		return (NULL);
	while (nb_tmp[i])
		i++;
	if (!(env->data = ft_memalloc(6 + i + 1)))
		return (NULL);
	ft_strcpy(env->data, "SHLVL=");
	ft_strcat(env->data, nb_tmp);
	free(nb_tmp);
	return (env);
}

char			*env_get(t_env_list *env, char *s)
{
	while (env)
	{
		if (!ft_strncmp(env->data, s, ft_strlen(s))
					&& env->data[ft_strlen(s)] == '=')
			return (env->data + ft_strlen(s) + 1);
		env = env->next;
	}
	return (NULL);
}

t_env_list		*env_init(char **env)
{
	t_env_list	*new;

	if (!env)
		return (NULL);
	if (!(new = ft_memalloc(sizeof(t_env_list))))
		return (NULL);
	if (*env && ft_strncmp(*env, "SHLVL=", 6)
			&& (!(new->data = ft_strdup(*env))))
		return (NULL);
	else if (*env && !ft_strncmp(*env, "SHLVL=", 6))
	{
		if (!(env_shlvl(new, *env)))
			return (NULL);
	}
	if (*env && *(env + 1))
	{
		if (!(new->next = env_init(env + 1)))
			return (NULL);
	}
	else
		new->next = NULL;
	return (new);
}

void			env_print(t_env_list *env)
{
	while (env)
	{
		ft_printf("%s\n", env->data);
		env = env->next;
	}
}

void			env_destroy(t_env_list *env)
{
	if (!env)
		return ;
	if (env->next)
		env_destroy(env->next);
	free(env->data);
	free(env);
}
