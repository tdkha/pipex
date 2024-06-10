/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_smart.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:13:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 18:11:04 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char *ft_skip_quote(const char **s) {
    char quote_char = **s;

    (*s)++;
    while (**s) {
        if (**s == quote_char) {
            (*s)++;
            return *s;
        }
        if (**s == '\\' && *(*s + 1) == quote_char) {
            (*s) += 2;
        } else {
            (*s)++;
        }
    }
    return NULL;
}

// Function to count words, accounting for quoted strings
static size_t ft_wordcount(const char *s, char delimiter) {
    size_t count = 0;

    while (*s) {
        ft_split_skip_delimiter(&s, delimiter);

        if (*s) {
            count++;
            if (*s == '\'' || *s == '\"') {
                if (!ft_skip_quote(&s)) {
                    break;
                }
            } else {
                while (*s && *s != delimiter && *s != '\'' && *s != '\"') {
                    s++;
                }
            }
        }
    }
    return count;
}

// Function to handle word extraction, including quoted words
static void helper_handler(const char **s, const char **start, size_t *cur_word_len, char delimiter) {
    if (**s == '\'' || **s == '\"') {
        char quote_char = **s;
        (*s)++;
        *start = *s - 1; // Include the starting quote
        while (**s) {
            if (**s == quote_char) {
                (*s)++;
                *cur_word_len = *s - *start;
                return;
            }
            if (**s == '\\' && *(*s + 1) == quote_char) {
                (*s) += 2;
            } else {
                (*s)++;
            }
        }
        *cur_word_len = *s - *start;
    } else {
        *start = *s;
        while (**s && **s != delimiter && **s != '\'' && **s != '\"') {
            (*s)++;
        }
        *cur_word_len = *s - *start;
    }
}

// Function to split the string, accounting for quoted strings
static char **ft_split_helper(char **res, const char *s, char delimiter, size_t i) {
    size_t cur_word_len;
    const char *start;

    while (*s) {
        ft_split_skip_delimiter(&s, delimiter);
        if (*s) {
            helper_handler(&s, &start, &cur_word_len, delimiter);
            res[i] = (char *)malloc((cur_word_len + 1) * sizeof(char));
            if (!res[i]) {
                ft_multiple_free_set_null(&res);
                return NULL;
            }
            ft_memcpy(res[i], start, cur_word_len);
            res[i][cur_word_len] = '\0';
            i++;
        }
    }
    res[i] = NULL;
    return res;
}

// Main function to split the string
char **ft_split_smart(const char *s, char delimiter) {
    char **res;
    size_t size = ft_wordcount(s, delimiter);

    res = (char **)malloc((size + 1) * sizeof(char *));
    if (!res) {
        return NULL;
    }
    return ft_split_helper(res, s, delimiter, 0);
}
