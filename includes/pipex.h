/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:04:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/06 22:23:34 by ktieu            ###   ########.fr       */
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

# define INPUT 0
# define OUTPUT 1


typedef enum 	s_error
{
	NO_ERROR,
	NO_PERMISSION,
	NO_FILE_OR_DIRECTORY,
	FAILED_MALLOC,
	FAILED_FORK,
	FAILED_PIPE,
	CMD_NOT_FOUND
}	t_error;

typedef enum s_redirect_type
{
	NORMAL,
	IN,
	OUT,
	HEREDOC
}	t_redirect_type;

typedef	struct s_redirect_end
{
	char	*name;
	int		fd;
}	t_redirect_end;

typedef	struct s_cmd_redirect
{
	t_redirect_type		type;
	t_redirect_end		from;
	t_redirect_end		to;
}	t_cmd_redirect;


typedef struct	s_cmd
{
	char			*cmd;
	char			*path;
	t_cmd_redirect	redirect;
}	t_cmd;

typedef struct s_shell
{
	int		ac;
	char	**av;
	char	**envp;
	int		cmd_count;
	pid_t	*process_pid;
	t_cmd	**cmds;
	// int		fd_infile;
	// int		fd_outfile;
	int		fds[2];
	t_error	error;
}	t_shell;


typedef struct s_cmd_parser
{
	char	*cmd;
	char	*path;
	int		cmd_found;
	int		cmd_parse;
	int 	here_doc;
	int		in;
	int		out;
	char	*redirect_file;
}	t_cmd_parser;

void	free_shell(t_shell **shell);
void	print_error(t_error err_code, char *str, t_shell **shell);
void	print_sys_error(t_error err_code, char *str, t_shell **shell);
void	parse_cmds(int ac, char **av, char **envp, t_shell **shell);
char	*find_path(char *command, char **envp);
t_shell	*shell_init(int ac, char **av, char	**envp);
t_cmd	*cmd_init(t_cmd_parser *parser, t_shell **shell);

#endif