/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:36:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 21:00:49 by ktieu            ###   ########.fr       */
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

	if (ac != 5)
	{
		ft_printf_fd(2, "pipex: bad arguments\n");
		exit(EXIT_FAILURE);
	}
	shell.ac = ac;
	shell.av = av;
	shell.envp = envp;
	shell.error = 0;
	ft_first_child(&shell);
	ft_ret_err(&shell);
}
