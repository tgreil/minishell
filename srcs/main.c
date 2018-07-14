/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t <t@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:50:40 by t                 #+#    #+#             */
/*   Updated: 2018/07/14 01:55:57 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_exiter(t_env_list *env, int status)
{
	env_destroy(env);
	return (status);
}

int		main(int ac, char **av, char **env)
{
	t_env_list	*env_list;
	char		*line;
	char		my_bool;

	(void)ac;
	(void)av;
	my_bool = TRUE;
	env_list = NULL;
	if (*env != NULL)
		if (!(env_list = env_init(env)))
			return (EXIT_ERROR);
	while (my_bool == TRUE)
	{
		prompt_print();
		if (get_next_line(0, &line) > 0 && cmd_exec(env_list, line) == E_SUC)
			free(line);
		else
			my_bool = FALSE;
	}
	if (line && !ft_strcmp(line, CMD_EXIT))
		free(line);
	return (minishell_exiter(env_list, EXIT_SUCCESS));
}
