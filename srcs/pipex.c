/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:05:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/05/30 16:13:32 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"



// void	ft_exec(char **argv, char **envp)
// {
	
// }

// void	child_process(int *fd, char **argv, char **envp)
// {
// 	char	*path;
// 	int		in_file;

// 	in_file = open(argv[1], O_RDONLY | O_CREAT, 0777);
// 	if (in_file == -1)
// 		ft_error();
// 	path = ft_find_path(argv, envp);
// 	close(fd[0]);
// 	dup2(in_file, STDIN_FILENO);
// 	dup2(fd[1], STDOUT_FILENO);
	
// }