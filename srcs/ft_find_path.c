/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:37:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 15:14:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*ft_is_valid_path(char **cmds)
{
	if (access(cmds[0], F_OK) == 0)
		return (ft_strdup(cmds[0]));
	else
	{
		ft_printf_fd(2, "pipex: %s: No such file or directory\n",
			cmds[0]);
		ft_multiple_free_set_null(&cmds);
		exit (127);
	}
}

static char	**find_env_path(char **paths, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
	{
		ft_printf_fd(2, "pipex: %s: No such file or directory\n", paths[0]);
		ft_multiple_free_set_null(&paths);
		exit (127);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*find_cmd_full_path(
	char **paths,
	char *command,
	char *cmd_full_path,
	t_shell *shell
)
{
	char	*full_path;
	int		i;

	i = 0;
	full_path = NULL;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		cmd_full_path = ft_strjoin(full_path, command);
		if (!full_path || !cmd_full_path)
		{
			ft_multiple_free_set_null(&paths);
			return (NULL);
		}
		free(full_path);
		if (access(cmd_full_path, F_OK) == 0)
		{
			ft_multiple_free_set_null(&paths);
			return (cmd_full_path);
		}
		free(cmd_full_path);
		i++;
	}
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
	cmd_full_path = NULL;
	paths = find_env_path(paths, shell->envp);
	if (!paths)
		return (NULL);
	cmd_full_path = find_cmd_full_path(paths, command, cmd_full_path, shell);
	if (!cmd_full_path)
	{
		ft_multiple_free_set_null(&paths);
		return (NULL);
	}
	return (cmd_full_path);
}
