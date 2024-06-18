/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:47:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/13 12:22:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static inline void	ft_heredoc_pipeline(pid_t *pid, int *fds)
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
		ft_printf_fd(2, "pipex: pipe error\n");
		exit(EXIT_FAILURE);
	}
}

static inline void	ft_heredoc_child_process(t_shell *shell, int *fds)
{
	char	*line;
	size_t	len;

	line = get_next_line(0);
	if (!line)
		exit(1);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (!ft_strcmp(line, shell->av[2]))
			break ;
		ft_printf_fd(fds[1], "%s", line);
		ft_printf_fd(fds[1], "%c", '\n');
		ft_free_set_null(&line);
		line = get_next_line(0);
	}
	if (line)
		ft_free_set_null(&line);
	else
		exit(1);
	close(fds[1]);
}

void	ft_heredoc(t_shell *shell)
{
	int		i;
	pid_t	pid;
	int		fds[2];

	i = 2;
	if (shell->ac < 6)
	{
		ft_printf_fd(2, "pipex: here_doc usage:\n ");
		ft_printf_fd(2, "./pipex here_doc LIMITER cmd1 cmd2 outfile\n");
		exit (EXIT_FAILURE);
	}
	ft_heredoc_pipeline(&pid, fds);
	if (pid == 0)
	{
		close(fds[0]);
		ft_heredoc_child_process(shell, fds);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fds[1]);
		ft_redirect_close_wait(shell, &pid, fds, i);
	}
}
