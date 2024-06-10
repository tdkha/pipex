/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:35:22 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 14:55:21 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec_error(t_shell *shell, char **cmds, char *path)
{
	if (!access(cmds[0], F_OK) && !access(cmds[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(cmds[0], '/'))
		{
			ft_printf_fd(2, "%s: %s: Is a directory\n", "pipex", cmds[0]);
			ft_multiple_free_set_null(&cmds);
			exit (126);
		}
		else
		{
			ft_printf_fd(2, "%s: %s: command not found\n", "pipex", cmds[0]);
			ft_multiple_free_set_null(&cmds);
			exit (127);
		}
	}
	ft_printf_fd(2, "pipex: %s: %s\n", path, strerror(errno));
	if (path)
		free(path);
	ft_multiple_free_set_null(&cmds);
	exit(NOT_EXECUTABLE);
}

void	ft_exec(t_shell *shell, char *cmd)
{
	char	*path;
	char	**cmds;
	char	*trimmed_cmd;

	trimmed_cmd = ft_strtrim(cmd, " ");
	if (!trimmed_cmd)
		exit(1);
	cmds = ft_split(trimmed_cmd, ' ');
	if (!cmds)
	{
		free(trimmed_cmd);
		exit(1);
	}
	free(trimmed_cmd);
	path = ft_find_path(cmds, shell);
	if (!path)
	{
		ft_printf_fd(2, "pipex: %s: command not found\n", cmds[0]);
		ft_multiple_free_set_null(&cmds);
		exit (127);
	}
	execve(path, cmds, shell->envp);
	ft_exec_error(shell, cmds, path);
}
