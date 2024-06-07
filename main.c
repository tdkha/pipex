/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:06:15 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/07 14:51:02 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char	**av, char **envp)
{
	t_shell	*shell;
	pid_t	pid1;
	int		fd[2];

	if (ac != 5)
	{
		ft_putstr_fd("Bad arguments\n", 2);
		exit(EXIT_FAILURE);
	}


	shell = shell_init(ac, av, envp);

	int i = 0;
	printf("\033[0;31mShell exists\033[0m: %s\n", shell->cmds[i] ? "yes" : "no");
	while (shell->cmds[i])
	{
		char 	*type;
		char	*file;
		if (shell->cmds[i]->redirect.type == IN)
		{
			type = "IN";
			file = shell->cmds[i]->redirect.from.name;
		}
		else if (shell->cmds[i]->redirect.type == OUT)
		{
			type = "OUT";
			file = shell->cmds[i]->redirect.to.name;
		}
		else if (shell->cmds[i]->redirect.type == HEREDOC)
		{
			type = "HEREDOC";
		}
		printf("\033[0;31mCmd %d\033[0m: %s, \033[0;31mType\033[0m: %s, \033[0;31mFile\033[0m: %s\n", i, shell->cmds[i]->cmd, type, file);
		i++;
	}
	shell_execute_cmds(&shell);
	free_shell(&shell);
	return (0);
}
