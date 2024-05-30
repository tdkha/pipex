/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:06:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/05/30 17:52:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error()
{
	perror("Error: ");
	exit(EXIT_FAILURE);
}

char	*transform(char *str)
{
	int	i;
	
	i = 0;
	while(str[i] != '\0')
	{
		while (str[i] == ' ')
		{
			i++;
		}
	}
	
}


char	**ft_sanitize_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < argc)
	{
		while (argv[i])
		{
			
		}
	}
}

char	*ft_find_path(char *command, char **envp)
{
	char	*path;
	
	if (!command)
		return (NULL);
			
}