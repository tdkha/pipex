/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:28:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 14:35:51 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	count;
	int	wrote;

	wrote = 0;
	count = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
	{
		wrote = ft_print_char((int)*str);
		if (wrote < 0)
			return (-1);
		count++;
		str++;
	}
	return (count);
}

int	ft_print_str_fd(char *str, int fd)
{
	int		count;
	ssize_t	wrote;
	size_t	len;
	char	*start;

	wrote = 0;
	count = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	start = str;
	len = ft_strlen(str);
	while (*str)
	{
		count++;
		str++;
	}
	wrote = write(fd, start, len);
	if (wrote != (int)len)
		return (-1);
	return (count);
}
