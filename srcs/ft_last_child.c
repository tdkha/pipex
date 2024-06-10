/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:11:17 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 10:22:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_open_outfile(t_shell *shell, int *fds)
{
	shell->fd_outfile = open(shell->av[shell->ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (shell->fd_outfile == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n", shell->av[shell->ac - 1], strerror(errno));
		close(fds[INPUT]);
		exit(EXIT_FAILURE);
	}
}

int	ft_last_child(t_shell *shell, int *prev_fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(prev_fds[INPUT]);
		ft_printf_fd(2, "pipex: fork error\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		ft_open_outfile(shell, prev_fds);
		ft_dup2(
			prev_fds[INPUT], STDIN_FILENO,
			shell->fd_outfile, STDOUT_FILENO);
		ft_exec(shell, shell->av[shell->ac - 2]);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}