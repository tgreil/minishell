/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: t <t@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 15:50:40 by t                 #+#    #+#             */
/*   Updated: 2018/07/21 16:50:59 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

# define EXIT_SUCCESS	0
# define E_SUC			EXIT_SUCCESS
# define EXIT_EXIT		1
# define E_EX			EXIT_EXIT
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
char			*env_get(t_env_list *env, char *s);
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
int				cmd_parser_split_increment(char *line, int *i, char **arg);
int				cmd_parser_split(char **arg, char *line, int *i);
t_cmd			*cmd_parser(char *line);
int				cmd_exec(t_env_list **env, char *line);

/*
**			cmd_parser.c
*/
int				cmd_parser_interpret(t_cmd *cmd, t_env_list *env);

/*
**			cmd_parser_replace.c
*/
char			*cmd_parser_replace(char *s, t_env_list *env);

/*
**			exec_access.c
*/
void			exec_free_paths(char **paths);
int				exec_chdmod(char *path);
char			**exec_get_paths(t_env_list *env);
int				exec_direct_access(t_cmd *cmd, t_env_list *env);
int				exec_access(t_cmd *cmd, t_env_list **env);

/*
**			forkator.c
*/
char			**forkator_env(t_env_list *env);
int				forkator(t_cmd *cmd, t_env_list *env, char *path);

/*
**			builtin_search.c
*/
void			builtin_initiate_tab(int (**pf)(t_cmd*, t_env_list**));
int				builtin_search(t_cmd *cmd, t_env_list **env);

/*
**			builtin_echo.c
*/
int				builtin_echo(t_cmd *cmd, t_env_list **env);

/*
**			builtin_env,c
*/
void			builtin_env_free(t_cmd *cmd, t_env_list *env_l, char **env_tab);
t_cmd			*builtin_create_cmd_tmp(t_cmd *cmd);
char			**builtin_env_create_env_tmp(t_cmd *cmd);
int				builtin_env_tmp(t_cmd *cmd);
int				builtin_env(t_cmd *cmd, t_env_list **env);

/*
**			builtin_setenv.c
*/
size_t			builtin_setenv_strlen_envname(char *env);
t_env_list		*builtin_setenv_new_env(char *new_env, t_env_list *env);
int				builtin_setenv(t_cmd *cmd, t_env_list **env);

/*
**			builtin_unsetenv.c
*/
void			builtin_unsetenv_remove(t_env_list *current, t_env_list *prev);
int				builtin_unsetenv(t_cmd *cmd, t_env_list **env);

/*
**			builtin_cd.c
*/
int				builtin_cd_reverse(t_env_list **env, char *current_dir);
int				builtin_cd_absolute_path(t_cmd *c, t_env_list **e, char *c_dir);
int				builtin_cd_home(t_env_list **env, char *current_dir);
int				builtin_cd(t_cmd *cmd, t_env_list **env);

/*
**			builtin_cd_envmodifier.c
*/
int				builtin_cd_create_env(t_env_list **e, char *env_n, char *path);
int				builtin_cd_change_env(t_env_list **env, char *name, char *path);

/*
**			error.c
*/
int				error(char *prog, char *msg, char *cmd, int ret);

#endif
