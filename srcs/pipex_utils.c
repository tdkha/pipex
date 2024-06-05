/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:06:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/05 15:13:48 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char *command, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*cmd_full_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while(paths[i])
	{
		full_path = ft_strjoin(paths[i],"/");
		cmd_full_path = ft_strjoin(full_path, command);
		ft_free_set_null(&full_path);
		if (access(cmd_full_path, F_OK) == 0)
			return (cmd_full_path);
		ft_free_set_null(&cmd_full_path);
		i++;
	}
	ft_multiple_free_set_null(paths);
	return (NULL);
}

void free_shell(t_shell **shell)
{
    if (shell && *shell) {
        if ((*shell)->cmds) {
            for (int i = 0; i <= (*shell)->cmd_count; i++) {
                if ((*shell)->cmds[i]) {
                    free((*shell)->cmds[i]->cmd);
                    free((*shell)->cmds[i]->path);
                    free((*shell)->cmds[i]);
                }
            }
            free((*shell)->cmds);
        }
        free(*shell);
        *shell = NULL;
    }
}