/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:37:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/09 21:35:04 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**find_env_path(char **paths, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
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

char	*ft_find_path(char *command, t_shell *shell)
{
	char	**paths;
	char	*cmd_full_path;

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
