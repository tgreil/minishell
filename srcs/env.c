/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t <t@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:50:40 by t                 #+#    #+#             */
/*   Updated: 2018/07/13 23:33:03 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list		*env_init(char **env)
{
	t_env_list	*new;

	if (!(new = malloc(sizeof(t_env_list))))
		return (NULL);
	if (!(new->data = ft_strdup(*env)))
		return (NULL);
	if (*(env + 1))
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
	if (env->next)
		env_destroy(env->next);
	free(env->data);
	free(env);
}
