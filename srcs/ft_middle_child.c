/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middle_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:54:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/13 12:08:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_middle_pipeline(pid_t *pid, int *fds, int *prev_fds)
{
	if (pipe(fds) == -1)
	{
		ft_printf_fd(2, "pipex: pipe error\n");
		exit(EXIT_FAILURE);
	}
	*pid = fork();
	if (*pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		close(prev_fds[0]);
		ft_printf_fd(2, "pipex: fork error\n");
		exit(1);
	}
}

void	ft_middle_child(t_shell *shell, int *prev_fd, int i)
{
	pid_t	pid;
	int		fds[2];

	ft_middle_pipeline(&pid, fds, prev_fd);
	if (pid == 0)
	{
		close(fds[0]);
		ft_dup2(
			prev_fd[0], STDIN_FILENO,
			fds[1], STDOUT_FILENO);
		ft_exec(shell, shell->av[i]);
	}
	else
	{
		close(fds[1]);
		ft_redirect_close_wait(shell, &pid, fds, i);
	}
}
