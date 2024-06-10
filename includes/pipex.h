/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:35:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/09 22:12:59 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <err.h>
#include <string.h>

# define INPUT 0
# define OUTPUT 1
# define NOT_EXECUTABLE 126
# define CMD_NOT_FOUND 127

typedef struct s_shell
{
	int		ac;
	char	**av;
	char	**envp;
	int		cmd_count;
	int		fd_infile;
	int		fd_outfile;
	int		error;
}	t_shell;


char	*ft_find_path(char *command, t_shell *shell);
void 	ft_exec(t_shell *shell, char *cmd);
int		ft_first_child(t_shell *shell);
int		ft_last_child(t_shell *shell, int *fds);
void	ft_dup2(
		int from_fd1,
		int to_fd1,
		int from_fd2,
		int to_fd2);
#endif