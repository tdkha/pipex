/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:59:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 15:15:35 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	while (av[i])
	{
		j = 0;
		split = ft_split_esc(av[i], ' ');
		printf("String %d\n", i);
		while (split[j])
		{
			printf("Split: %s\n", split[j]);
			j++;
		}
		printf("---------------------------\n");
		ft_multiple_free_set_null(&split);
		i++;
	}
}
