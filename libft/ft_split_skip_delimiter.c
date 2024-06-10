/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_skip_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:17:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 17:18:26 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_skip_delimiter(char const **s, char delimiter)
{
	while (**s && **s == delimiter)
		(*s)++;
}
