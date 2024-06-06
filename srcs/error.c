/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/06 16:10:49 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_sys_error(t_error err_code, char *str, t_shell **shell)
{
	if (err_code == FAILED_MALLOC)
	{	
		print_error(FAILED_MALLOC, "malloc_error", shell);
	}
	else if (err_code == FAILED_FORK)
	{
		print_error(FAILED_FORK, "fork_error", shell);
	}
	else if (err_code == FAILED_PIPE)
	{
		print_error(FAILED_FORK, "pipe_error", shell);
	}
}

void	print_error(t_error err_code, char *str, t_shell **shell)
{
	ft_putstr_fd("pipex: ", 2);
	if (err_code == FAILED_MALLOC
		|| err_code == FAILED_FORK)
	{
		perror(str);
	}
	else if (err_code == NO_FILE)
	{
		ft_putstr_fd("No such file or directory", 2);
	}
	free_shell(shell);
	exit(EXIT_FAILURE);
}