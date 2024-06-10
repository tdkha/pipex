/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:35:22 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/09 22:01:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_exec_error(t_shell *shell, char **cmds, char *path)
{
	// if (!access(cmds[0], F_OK))
	// {
		
	// }
	ft_printf_fd(2, "pipex: %s: %s\n", path, strerror(errno));
	if (path)
		free(path);
	ft_multiple_free_set_null(&cmds);
	exit(NOT_EXECUTABLE);
}

void ft_exec(t_shell *shell, char *cmd)
{
	char	*path;
	char	**cmds;
	char	*trimmed_cmd;

	trimmed_cmd = ft_strtrim(cmd, " ");
	if (!trimmed_cmd)
		exit(EXIT_FAILURE);
	cmds = ft_split(trimmed_cmd, " ");
	if (!cmds)
	{
		free(trimmed_cmd);
		exit(EXIT_FAILURE);
	}
	free(trimmed_cmd);
	path = ft_find_path(cmds[0], shell);
	if (!path)
	{
		ft_multiple_free_set_null(&cmds);
		ft_printf_fd(2, "pipex: %s: %s\n", cmds[0], "command not found");
		exit(127);
	}
	execve(path, cmds, shell->envp);
	ft_exec_error(shell, cmds, path);
}
