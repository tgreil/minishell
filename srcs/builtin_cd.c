/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 13:10:26 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/21 15:43:51 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			builtin_cd_relative_path(t_cmd *cmd, t_env_list **env,
		char *current_dir)
{
	char		full_path[PATH_MAX];
	char		*ptr;

	if ((ft_strlen(current_dir) + ft_strlen(cmd->arg[1]) + 1) > PATH_MAX)
		return (EXIT_SUCCESS);
	ft_strcpy(full_path, current_dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd->arg[1]);
	if (!chdir(full_path))
	{
		if ((builtin_cd_change_env(env, "OLDPWD=", current_dir)) < 0)
			return (EXIT_ERROR);
		if (!(ptr = getcwd(current_dir, PATH_MAX)))
			return (EXIT_ERROR);
		if ((builtin_cd_change_env(env, "PWD=", current_dir)) < 0)
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

int			builtin_cd_reverse(t_env_list **env, char *current_dir)
{
	t_env_list		*lst;
	char			*ptr;

	lst = *env;
	while (lst && lst->data && ft_strncmp(lst->data, "OLDPWD=", 7))
		lst = lst->next;
	if (!lst)
		ft_printf("cd: OLDPWD not set\n"); //achanger vers le fd2
	else
	{
		if (!chdir(&lst->data[7]))
		{
			if ((builtin_cd_change_env(env, "OLDPWD=", current_dir)) < 0)
				return (EXIT_ERROR);
			if (!(ptr = getcwd(current_dir, PATH_MAX)))
				return (EXIT_ERROR);
			if ((builtin_cd_change_env(env, "PWD=", current_dir)) < 0)
				return (EXIT_ERROR);
		}
	}
	return (EXIT_SUCCESS);
}

int			builtin_cd_absolute_path(t_cmd *cmd, t_env_list **env,
		char *current_dir)
{
	char			*ptr;

	if (!chdir(cmd->arg[1]))
	{
		if ((builtin_cd_change_env(env, "OLDPWD=", current_dir)) < 0)
			return (EXIT_ERROR);
		if (!(ptr = getcwd(current_dir, PATH_MAX)))
			return (EXIT_ERROR);
		if ((builtin_cd_change_env(env, "PWD=", current_dir)) < 0)
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

int			builtin_cd_home(t_env_list **env, char *current_dir)
{
	t_env_list		*lst;
	char			*ptr;

	lst = *env;
	while (lst && lst->data && ft_strncmp(lst->data, "HOME=", 5))
		lst = lst->next;
	if (!lst || !lst->data)
		return (error("cd:", "HOME", "not set", EXIT_SUCCESS));
	if (!chdir(&lst->data[5]))
	{
		if ((builtin_cd_change_env(env, "OLDPWD=", current_dir)) < 0)
			return (EXIT_ERROR);
		if (!(ptr = getcwd(current_dir, PATH_MAX)))
			return (EXIT_ERROR);
		if ((builtin_cd_change_env(env, "PWD=", current_dir)) < 0)
			return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

int			builtin_cd(t_cmd *cmd, t_env_list **env)
{
	char		current_dir[PATH_MAX];
	char		*ptr;

	if (!(ptr = getcwd(current_dir, PATH_MAX)))
		return (EXIT_SUCCESS); //mettre un message d'erreur? exit? NOPE ? fonction autorise? OUI
	else if (!cmd->arg[1])
		return (builtin_cd_home(env, current_dir));
	else if (cmd->arg[1][0] == '/')
		return (builtin_cd_absolute_path(cmd, env, current_dir));
	else if (cmd->arg[1][0] == '-')
		return (builtin_cd_reverse(env, current_dir));
	return (builtin_cd_relative_path(cmd, env, current_dir));
}
