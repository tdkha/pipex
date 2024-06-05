/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:45:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/05 14:57:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error(t_error err_code, char *str, t_shell **shell)
{
	ft_putstr_fd("pipex: ", 2);
	if (err_code == FAILED_MALLOC)
	{
		free_shell(shell);
		ft_putstr_fd("failed to malloc", 2);
	}
	else if (err_code == NO_FILE)
	{
		ft_putstr_fd("No such file or directory", 2);
	}
	exit(EXIT_FAILURE);
}