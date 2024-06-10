/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:02:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 14:35:39 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_format(const char *format, va_list ap)
{
	size_t	i;
	int		count;
	int		wrote;

	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			wrote = ft_print_format(format[++i], ap);
		else
			wrote = write(1, &format[i], 1);
		if (wrote == -1)
			return (-1);
		count += wrote;
		i++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = ft_parse_format(format, ap);
	va_end(ap);
	return (count);
}

static int	ft_parse_format_fd(int fd, const char *format, va_list ap)
{
	size_t	i;
	int		count;
	int		wrote;

	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			wrote = ft_print_format_fd(fd, format[++i], ap);
		else
			wrote = write(fd, &format[i], 1);
		if (wrote == -1)
			return (-1);
		count += wrote;
		i++;
	}
	return (count);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = ft_parse_format_fd(fd, format, ap);
	va_end(ap);
	return (count);
}
