/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t <t@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:50:40 by t                 #+#    #+#             */
/*   Updated: 2018/07/18 13:46:56 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define EXIT_SUCCESS	0
# define E_SUC			EXIT_SUCCESS
# define EXIT_EXIT		1
# define EXIT_ERROR		-1
# define CMD_EXIT		"exit"

typedef struct			s_env_list
{
	char				*data;
	struct s_env_list	*next;
}						t_env_list;

typedef struct			s_cmd
{
	char				**arg;
	struct s_cmd		*next;
}						t_cmd;

typedef struct			s_builtin
{
	char				*name;
	int					pos;
}						t_builtin;

/*
**			main.c
*/
int				minishell_exiter(t_env_list *env, int status);
int				main(int ac, char **av, char **env);

/*
**			env.c
*/
t_env_list		*env_init(char **env);
void			env_print(t_env_list *env);
void			env_destroy(t_env_list *env);

/*
**			prompt.c
*/
void			prompt_print();

/*
**			cmd_exec.c
*/
char			cmd_parser_split_end(char **arg, char *line, int *i);
int				cmd_parser_split(char **arg, char *line, int *i);
t_cmd			*cmd_parser(char *line);
int				cmd_exec(t_env_list *env, char *line);

/*
**			exec_access.c
*/
void			exec_free_paths(char **paths);
int				exec_chdmod(char *path);
char			**exec_get_paths(t_env_list *env);
int				exec_direct_access(t_cmd *cmd, t_env_list *env);
int				exec_access(t_cmd *cmd, t_env_list *env);

/*
**			forkator.c
*/
char			**forkator_env(t_env_list *env);
int				forkator(t_cmd *cmd, t_env_list *env, char *path);

/*
**			builtin_struct.c
*/
void			builtin_initiate_tab(int (**pf)(t_cmd*, t_env_list*));
int				builtin_search(t_cmd *cmd, t_env_list *env);

#endif
