/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:37:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/13 17:29:44 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*ft_is_valid_path(char **cmds)
{
	if (access(cmds[0], F_OK) == 0)
		return (ft_strdup(cmds[0]));
	else
	{
		ft_printf_fd(2, "%s: %s: No such file or directory\n", "pipex", cmds[0]);
		ft_multiple_free_set_null(&cmds);
		exit(127);
	}
}

static char	**find_env_path(char **envp, char **cmds)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		ft_printf_fd(2, "%s: %s: No such file or directory\n", "pipex", cmds[0]);
		ft_multiple_free_set_null(&cmds);
		exit(127);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*find_cmd_full_path(char **paths, char *command)
{
	char	*full_path;
	char	*cmd_full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			ft_return_multiple_free_set_null(&paths);
		cmd_full_path = ft_strjoin(full_path, command);
		free(full_path);
		if (!cmd_full_path)
			ft_return_multiple_free_set_null(&paths);
		if (access(cmd_full_path, F_OK) == 0)
		{
			ft_multiple_free_set_null(&paths);
			return (cmd_full_path);
		}
		free(cmd_full_path);
		i++;
	}
	ft_multiple_free_set_null(&paths);
	return (NULL);
}

char	*ft_find_path(char **cmds, t_shell *shell)
{
	char	**paths;
	char	*cmd_full_path;
	char	*command;

	command = cmds[0];
	if (ft_strchr(command, '/'))
		return (ft_is_valid_path(cmds));
	paths = find_env_path(shell->envp, cmds);
	if (!paths)
		return (NULL);
	cmd_full_path = find_cmd_full_path(paths, command);
	if (!cmd_full_path)
	{
		return (NULL);
	}
	return (cmd_full_path);
}
