/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piliegeo <piliegeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 15:00:36 by piliegeo          #+#    #+#             */
/*   Updated: 2018/07/21 18:38:07 by tgreil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_free_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (EXIT_SUCCESS);
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
	char		**paths;
	t_env_list	*lst;

	lst = env;
	paths = NULL;
	while (lst && lst->data && ft_strncmp("PATH=", lst->data, 5))
		lst = lst->next;
	if (!lst || !lst->data || !(paths = ft_strsplit(&lst->data[5], ':')))
		return (NULL);
	return (paths);
}

int			exec_direct_access(t_cmd *cmd, t_env_list *env)
{
	struct stat		stat;

	(void)env;
	ft_bzero(&stat, sizeof(struct stat));
	lstat(cmd->arg[0], &stat);
	if ((!access(cmd->arg[0], stat.st_uid)
			|| !access(cmd->arg[0], stat.st_gid))
			&& exec_chmod(cmd->arg[0]))
		return (forkator(cmd, env, cmd->arg[0]));
	return (error("minishell: ", "command not found:", cmd->arg[0], 0));
}

int			exec_access(t_cmd *cmd, t_env_list **env)
{
	char			path_exe[PATH_MAX];
	char			**paths;
	int				i;
	struct stat		stat;

	i = -1;
	paths = exec_get_paths(*env);
	while (paths && paths[++i])
	{
		if ((ft_strlen(paths[i]) + ft_strlen(cmd->arg[0]) + 1) < PATH_MAX)
		{
			ft_strcat(ft_strcpy(path_exe, paths[i]), "/");
			ft_strcat(path_exe, cmd->arg[0]);
			ft_bzero(&stat, sizeof(struct stat));
			lstat(path_exe, &stat);
			if ((!access(path_exe, stat.st_uid) || !access(path_exe,
							stat.st_gid)) && exec_chmod(path_exe))
			{
				forkator(cmd, *env, path_exe);
				return (exec_free_paths(paths));
			}
		}
	}
	i = (paths ? exec_free_paths(paths) : 0);
	return (exec_direct_access(cmd, *env));
}
