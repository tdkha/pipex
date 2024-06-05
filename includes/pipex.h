/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:04:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/05 14:43:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <err.h>

typedef enum 	s_error
{
	NO_ERROR,
	NO_PERMISSION,
	NO_FILE,
	FAILED_MALLOC,
	CMD_NOT_FOUND
}	t_error;

typedef struct	s_cmd
{
	char		*cmd;
	char		*path;
}	t_cmd;

typedef struct s_shell
{
	int		ac;
	char	**av;
	char	**envp;
	int		cmd_count;
	t_cmd	**cmds; // one command on the terminal
	int		fd_infile;
	int		fd_outfile;
	int		fds[2];
	t_error	error;

}	t_shell;


typedef struct s_cmd_parser
{
	char	*cmd;
	int		cmd_found;
	int 	here_doc;
	int		in;
	int		out;
}	t_cmd_parser;

void	free_shell(t_shell **shell);
void	print_error(t_error err_code, char *str, t_shell **shell);
void	parse_cmds(int ac, char **av, char **envp, t_shell **shell);
char	*find_path(char *command, char **envp);
t_shell	*shell_init(int ac, char **av, char	**envp);
t_cmd	*cmd_init(char *cmd, char *path, t_shell **shell);

#endif