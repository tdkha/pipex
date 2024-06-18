/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_close_wait.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 22:03:43 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 23:07:54 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_redirect_close_wait(
	t_shell *shell,
	int *pid,
	int *fds,
	int current_index)
{
	int	next_index;
	int	last_index;

	last_index = shell->ac - 2;
	next_index = current_index + 1;
	if (next_index < last_index)
		ft_middle_child(shell, fds, next_index);
	else if (next_index == last_index)
		ft_last_child(shell, fds);
	close(fds[0]);
	waitpid(*pid, NULL, 0);
}
