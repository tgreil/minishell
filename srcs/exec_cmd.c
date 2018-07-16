/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:00:36 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/15 19:55:24 by piliegeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_free_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

int			exec_chmod(char *path)
{
	struct stat	stat;

	lstat(path, &stat);
	if (S_ISLNK(stat.st_mode) == 1)
		return (0);
	else if (S_ISFIFO(stat.st_mode) == 1)
		return (0);
	else if (S_ISBLK(stat.st_mode) == 1)
		return (0);
	else if (S_ISCHR(stat.st_mode) == 1)
		return (0);
	else if (S_ISSOCK(stat.st_mode) == 1)
		return (0);
	else if (S_ISDIR(stat.st_mode) == 1)
		return (0);
	return (1);
}

char		**exec_get_paths(t_env_list *env)
{
	char **paths;
	t_env_list *lst;

	lst = env;
	while (lst && ft_strncmp("PATH=", lst->data, 5))
		lst = lst->next;
	if (!lst || !(paths = ft_strsplit(&lst->data[5], ':')))
		return (NULL);
	return (paths);
}

int			exec_direct_access(t_cmd *cmd, t_env_list *env)
{
	struct stat		stat;

	(void)env;
	lstat(cmd->arg[0], &stat);
	if ((!access(cmd->arg[0], stat.st_uid)
			|| !access(cmd->arg[0], stat.st_gid))
			&& exec_chmod(cmd->arg[0]))
		return (forkator(cmd, env, cmd->arg[0]));
	return (0);
}

int			exec_access(t_cmd *cmd, t_env_list *env)
{
	char			path_exec[PATH_MAX];
	char			**paths;
	int				i;
	struct stat		stat;

	i = 0;
	if (!(paths = exec_get_paths(env)))
		return (EXIT_ERROR);
	while (paths[i])
	{
		if ((ft_strlen(paths[i]) + ft_strlen(cmd->arg[0]) + 1) < PATH_MAX)
		{
			ft_strcpy(path_exec, paths[i]);
			ft_strcat(path_exec, "/");
			ft_strcat(path_exec, cmd->arg[0]);
			lstat(path_exec, &stat);
			if ((!access(path_exec, stat.st_uid)
					|| !access(path_exec, stat.st_gid))
					&& exec_chmod(path_exec))
			{
				forkator(cmd, env, path_exec);
				exec_free_paths(paths);
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	exec_free_paths(paths);
	return (exec_direct_access(cmd, env));
}
