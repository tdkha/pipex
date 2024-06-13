/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:35:22 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/13 16:49:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static inline void	ft_empty_cmd(char *trimmed_cmd, char *org_cmd)
{
	if (trimmed_cmd[0] == ' ' || !trimmed_cmd[0])
		ft_printf_fd(2, "pipex: %s: command not found\n", org_cmd);
	else
		ft_printf_fd(2, "pipex: permission denied:\n");
	exit (127);
}

static inline void	ft_no_path(char **cmds)
{
	ft_printf_fd(2, "%s: %s: command not found\n", "pipex", cmds[0]);
	ft_multiple_free_set_null(&cmds);
	exit (127);
}

void	ft_exec_error(char **cmds, char *path)
{
	if (!access(cmds[0], F_OK) && !access(cmds[0], X_OK))
	{
		if (path)
			free(path);
		if (ft_strchr(cmds[0], '/'))
		{
			ft_printf_fd(2, "pipex: %s: Is a directory\n", cmds[0]);
			ft_multiple_free_set_null(&cmds);
			exit (126);
		}
		else
		{
			ft_printf_fd(2, "pipex: %s: command not found\n", cmds[0]);
			ft_multiple_free_set_null(&cmds);
			exit (127);
		}
	}
	ft_printf_fd(2, "pipex: %s: %s\n", path, strerror(errno));
	if (path)
		free(path);
	ft_multiple_free_set_null(&cmds);
	exit(FT_NOT_EXECUTABLE);
}

void	ft_exec(t_shell *shell, char *cmd)
{
	char	*path;
	char	**cmds;
	char	*trimmed_cmd;

	trimmed_cmd = ft_strtrim(cmd, " ");
	if (!trimmed_cmd)
		exit(1);
	if (!*trimmed_cmd)
		ft_empty_cmd(trimmed_cmd, cmd);
	cmds = ft_split_esc(trimmed_cmd, ' ');
	if (!cmds)
	{
		free(trimmed_cmd);
		exit(1);
	}
	free(trimmed_cmd);
	path = ft_find_path(cmds, shell);
	if (!path)
		ft_no_path(cmds);
	execve(path, cmds, shell->envp);
	ft_exec_error(cmds, path);
}
