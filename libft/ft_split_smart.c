/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_smart.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:13:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 17:34:09 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_skip_quote(const char **s)
{
	char		quote_char;
	const char	*end;

	quote_char = **s;
	(*s)++;
	end = ft_strchr(*s, quote_char);
	if (end)
	{
		*s = end + 1;
		return (end);
	}
	else
	{
		*s += ft_strlen(*s);
		return (NULL);
	}
}

static size_t	ft_wordcount(const char *s, char delimiter)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		ft_split_skip_delimiter(&s, delimiter);
		if (*s)
		{
			count++;
			if (*s == '\'' || *s == '\"')
			{
				if (!ft_skip_quote(&s))
					break ;
			}
			else
			{
				while (*s && *s != delimiter && *s != '\'' && *s != '\"')
					s++;
			}
		}
	}
	return (count);
}

static void	helper_handler(
	const char **s,
	const char **start,
	size_t *cur_word_len,
	char delimiter)
{
	char	quote_char;

	if (**s == '\'' || **s == '\"')
	{
		quote_char = **s;
		(*s)++;
		*start = *s;
		while (**s && **s != quote_char)
			(*s)++;
		*cur_word_len = *s - *start;
		if (**s == quote_char)
			(*s)++;
	}
	else
	{
		*start = *s;
		while (**s && **s != delimiter && **s != '\'' && **s != '\"')
			(*s)++;
		*cur_word_len = *s - *start;
	}
}

static char	**ft_split_helper(
	char **res,
	const char *s,
	char delimiter,
	size_t i)
{
	size_t		cur_word_len;
	const char	*start;

	while (*s)
	{
		ft_split_skip_delimiter(&s, delimiter);
		if (*s)
		{
			helper_handler(&s, &start, &cur_word_len, delimiter);
			res[i] = (char *)malloc((cur_word_len + 1) * sizeof(char));
			if (!res[i])
			{
				ft_multiple_free_set_null(&res);
				return (NULL);
			}
			ft_memcpy(res[i], start, cur_word_len);
			res[i][cur_word_len] = '\0';
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split_smart(const char *s, char delimiter)
{
	char	**res;
	size_t	size;

	size = ft_wordcount(s, delimiter);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_split_helper(res, s, delimiter, 0));
}

// int main() {
//     char *string = "Hello! \"We    are\" are the 'best'";
//     char **str = ft_split_smart(string, ' ');

//     for (int i = 0; str[i] != NULL; i++) {
//         printf("Word %d: %s\n", i, str[i]);
//         free(str[i]);
//     }
//     free(str);

//     return 0;
// }