/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:35:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/10 14:54:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <err.h>
# include <string.h>

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

char	*ft_find_path(char **cmds, t_shell *shell);
void	ft_exec(t_shell *shell, char *cmd);
void	ft_first_child(t_shell *shell);
void	ft_last_child(t_shell *shell, int *prev_fds);
void	ft_redirect_close_wait(
			t_shell *shell,
			int *pid,
			int *fds,
			int current_index);
void	ft_dup2(
			int from_fd1,
			int to_fd1,
			int from_fd2,
			int to_fd2);
#endif