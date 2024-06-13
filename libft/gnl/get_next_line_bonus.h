/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:24:43 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 22:41:48 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

/*-----------------------------------------------------------------------*/
/*							HELPER FUNCTIONS                                */
/*-----------------------------------------------------------------------*/

char	*ft_strjoin_gnl(char *s1, char *s2, int *eol_index);
void	ft_strlcpy_gnl(char *dst, const char *src, size_t dst_size);

/*-----------------------------------------------------------------------*/
/*							MAIN FUNCTIONS									*/
/*-----------------------------------------------------------------------*/
char	*get_next_line_bonus(int fd);

#endif