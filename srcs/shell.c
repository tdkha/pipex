/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:35:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/05 15:11:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmd	*cmd_init(char *cmd, char *path, t_shell **shell)
{
	t_cmd	*res;

	res = (t_cmd *) malloc (sizeof(t_cmd));
	if (!res)
		print_error(FAILED_MALLOC, NULL, shell);
	res->cmd = cmd;
	res->path = path;
	return (res);
}


t_shell *shell_init(int ac, char **av, char **envp) {
    t_shell *shell;

    shell = (t_shell *)malloc(sizeof(t_shell));
    if (!shell) {
        print_error(FAILED_MALLOC, NULL, &shell);
        return NULL;
    }
    shell->ac = ac;
    shell->av = av;
    shell->envp = envp;
    shell->error = NO_ERROR;
    shell->cmd_count = ac - 3;
    printf("Command count: %d\n", shell->cmd_count);

    shell->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (shell->cmd_count + 1));
    if (!shell->cmds) {
        print_error(FAILED_MALLOC, NULL, &shell);
        return NULL;
    }
    for (int i = 0; i <= shell->cmd_count; i++) {
        shell->cmds[i] = NULL; // Initialize command pointers to NULL
    }

	parse_cmds(ac, av, envp, &shell);
    return (shell);
}
