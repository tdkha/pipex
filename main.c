/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:06:15 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/05 15:20:44 by ktieu            ###   ########.fr       */
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
	printf("Shell: %s\n", shell->cmds[i] ? "yes" : "no");
	while (shell->cmds[i])
	{
		printf("Cmd %d: %s\n", i, shell->cmds[i]->cmd);
		i++;
	}

	free_shell(&shell);
	// if (pipe(fd) == -1)
	// 	ft_error();
		
	// pid1 = fork();
	// if (pid1 == -1)
	// 	ft_error();
		
	// if (pid1 == 0)
	// 	child_process(fd, argv, envp);
	// else
	// {
	// 	close(fd[1]);
	// 	print
	// }

	//char	*path;
	
	// int i= 0;
	// while (envp[i] != NULL)
	// {
	// 	printf("%s\n", envp[i]);
	// 	i++;
	// }
	return (0);
}
