/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_close_wait.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:03:43 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/09 22:05:53 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_redirect_close_wait(t_shell *shell, int *pid, int *fds, int current_index)
{
	int next_index;

	next_index = current_index + 1;
	// if (next_index == shell->ac - 2)
	// {
		ft_last_child(shell, fds);
	// }
	close(fds[INPUT]);
	waitpid(*pid, NULL, 0);
}