/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/06 17:56:47 by ktieu            ###   ########.fr       */
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
		return ;
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (err_code == NO_FILE_OR_DIRECTORY)
	{
		ft_putendl_fd(strerror(2), 2);
	}
	else if (err_code == NO_PERMISSION)
	{
		ft_putendl_fd(strerror(13), 2);
	}
	free_shell(shell);
	exit(EXIT_FAILURE);
}