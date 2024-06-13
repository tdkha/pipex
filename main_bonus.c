/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:51:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 22:59:19 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

static inline void	ft_ret_err(t_shell *shell)
{
	int	error;

	error = (shell->error & 0xff00) >> 8;
	exit (error);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac < 5)
	{
		ft_printf_fd(2, "pipex: bad arguments\n");
		exit(EXIT_FAILURE);
	}
	shell.ac = ac;
	shell.av = av;
	shell.envp = envp;
	shell.error = 0;
	if (ft_strncmp(av[1], "here_doc", sizeof("here_doc")) == 0)
		ft_heredoc(&shell);
	else
		ft_first_child(&shell);
	ft_ret_err(&shell);
}
