/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:42:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 14:48:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_open_infile(t_shell *shell, int *fds)
{
	shell->fd_infile = open(shell->av[1], O_RDONLY);
	if (shell->fd_infile == -1)
	{
		ft_printf_fd(2, "pipex: %s: %s\n", shell->av[1], strerror(errno));
		close(fds[1]);
		exit(1);
	}
}

static void	ft_first_pipeline(pid_t *pid, int *fds)
{
	if (pipe(fds) == -1)
	{
		ft_printf_fd(2, "pipex: pipe error\n");
		exit(1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		ft_printf_fd(2, "pipex: fork error\n");
		exit(1);
	}
}

void	ft_first_child(t_shell *shell)
{
	int		i;
	pid_t	pid;
	int		fds[2];

	i = shell->ac - shell->cmd_count - 1;
	ft_first_pipeline(&pid, fds);
	if (pid == 0)
	{
		close(fds[0]);
		ft_open_infile(shell, fds);
		ft_dup2(
			shell->fd_infile, STDIN_FILENO,
			fds[1], STDOUT_FILENO);
		ft_exec(shell, shell->av[2]);
	}
	else
	{
		close(fds[1]);
		ft_redirect_close_wait(shell, &pid, fds, i);
	}
}
