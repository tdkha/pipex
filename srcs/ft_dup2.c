/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:35:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/09 21:35:15 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_dup2(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
{
	dup2(from_fd1, to_fd1);
	close(from_fd1);
	dup2(from_fd2, to_fd2);
	close(from_fd2);
}
