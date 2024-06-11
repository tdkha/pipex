/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:59:59 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/11 10:04:50 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	main(int ac, char ** av, char envp)
{
	int i = 0;
	int j = 0;
	char	**split;

	while (av[i])
	{
		j = 0;
		split = ft_split_smart(av[i], ' ');
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