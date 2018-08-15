/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 15:00:46 by piliegeo          #+#    #+#             */
/*   Updated: 2018/08/03 15:00:47 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_exiter(t_env_list *env, int status)
{
	env_destroy(env);
	return (status);
}

void	control_c_handler(int nbr)
{
	ft_printf("\n", nbr);
	prompt_print();
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
	signal(SIGINT, &control_c_handler);
	while (my_bool == TRUE)
	{
		prompt_print();
		if (get_next_line(0, &line) > 0 && cmd_exec(&env_list, line) != E_EX)
			free(line);
		else
			my_bool = FALSE;
	}
	if (line && !ft_strcmp(line, CMD_EXIT))
		free(line);
	return (minishell_exiter(env_list, EXIT_SUCCESS));
}
