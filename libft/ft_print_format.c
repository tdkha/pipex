/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:37:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 14:42:57 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_parse_format_specifier(char specifier, va_list ap,
	char *lower_base, char *upper_base)
{
	if (specifier == 'c')
		return (ft_print_char(va_arg(ap, int)));
	else if (specifier == 's')
		return (ft_print_str(va_arg(ap, char *)));
	else if (specifier == 'p')
		return (ft_print_ptr(va_arg(ap, unsigned long long)));
	else if (specifier == 'u')
		return (ft_print_num_base(va_arg(ap, unsigned int), 10, lower_base));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_print_num_base(va_arg(ap, int), 10, lower_base));
	else if (specifier == 'x')
		return (ft_print_num_base(va_arg(ap, unsigned int), 16, lower_base));
	else if (specifier == 'X')
		return (ft_print_num_base(va_arg(ap, unsigned int), 16, upper_base));
	else if (specifier == '%')
		return (ft_print_char(specifier));
	else
		return (-1);
}

int	ft_print_format(char specifier, va_list ap)
{
	int		count;
	char	*upper_base;
	char	*lower_base;

	upper_base = "0123456789ABCDEF";
	lower_base = "0123456789abcdef";
	count = 0;
	count = ft_parse_format_specifier(specifier, ap, lower_base, upper_base);
	return (count);
}

static int	ft_parse_format_specifier_fd(
	int fd,
	char specifier,
	va_list ap,
	char *upper_base)
{
	char	*lower_base;

	lower_base = "0123456789abcdef";
	if (specifier == 'c')
		return (ft_print_char_fd(va_arg(ap, int), fd));
	else if (specifier == 's')
		return (ft_print_str_fd(va_arg(ap, char *), fd));
	else if (specifier == 'p')
		return (ft_print_ptr_fd(va_arg(ap, unsigned long long), fd));
	else if (specifier == 'u')
		return (
			ft_print_num_base_fd(va_arg(ap, unsigned int), 10, lower_base, fd));
	else if (specifier == 'd' || specifier == 'i')
		return (
			ft_print_num_base_fd(va_arg(ap, int), 10, lower_base, fd));
	else if (specifier == 'x')
		return (
			ft_print_num_base_fd(va_arg(ap, unsigned int), 16, lower_base, fd));
	else if (specifier == 'X')
		return (
			ft_print_num_base_fd(va_arg(ap, unsigned int), 16, upper_base, fd));
	else if (specifier == '%')
		return (ft_print_char_fd(specifier, fd));
	else
		return (-1);
}

int	ft_print_format_fd(int fd, char specifier, va_list ap)
{
	int		count;
	char	*upper_base;

	upper_base = "0123456789ABCDEF";
	count = 0;
	count = ft_parse_format_specifier_fd(fd, specifier, ap,
			upper_base);
	return (count);
}
