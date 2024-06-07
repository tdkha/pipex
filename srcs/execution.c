/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:34:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/07 08:40:49 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_process_execute(t_shell **shell)
{
	
}

void	child_process_execute(t_shell **shell)
{
	
}

static inline int	handle_open(
	t_shell **shell,
	t_cmd *current_cmd,
	t_redirect_type type
)
{
	char	*filename;
	int		fd_file_open;
	
	if (type == IN)
	{
		filename = current_cmd->redirect.from.name;
		current_cmd->redirect.from.fd = open(filename, O_RDONLY);
		fd_file_open = current_cmd->redirect.from.fd;
	}
	else if (type == OUT)
	{
		filename = current_cmd->redirect.to.name;
		current_cmd->redirect.to.fd = open(filename, O_RDONLY);
		fd_file_open = current_cmd->redirect.to.fd;
	}
	if (fd_file_open == -1 && access(filename, F_OK))
		print_error(NO_FILE_OR_DIRECTORY, filename, shell);
	else if (fd_file_open == -1 && !access(filename, F_OK))
		print_error(NO_PERMISSION, filename, shell);
}

static inline void	handle_dup_and_close(
	t_shell **shell,
	t_cmd *current_cmd,
	t_redirect_type type,
	int	fd_file_open
)
{
	if (type == IN)
	{
		dup2(current_cmd->redirect.from.fd, STDIN_FILENO); //IN
		dup2((*shell)->fds[OUTPUT], STDOUT_FILENO); // OUT
	}
	else if (type == OUT)
	{
		dup2((*shell)->fds[INPUT], STDIN_FILENO); // IN
		dup2(current_cmd->redirect.to.fd, STDOUT_FILENO); // OUT
	}
}

static inline void	handle_cmd_redirection(
	t_shell **shell,
	t_cmd *current_cmd
)
{
	t_redirect_type	type;
	char			*filename;
	int				fd_file_open;

	type = current_cmd->redirect.type;
	if (type == IN || type == OUT)
	{
		fd_file_open = handle_open(shell, current_cmd, type);
		handle_dup_and_close();
	}
}

void	shell_execute_cmds(t_shell **shell)
{
	t_cmd	*current_cmd;
	int		i;

	i = 0;
	while (i < 2)//(*shell)->cmd_count)
	{
		if (pipe((*shell)->fds) == -1)
			print_sys_error(FAILED_PIPE, NULL, shell);
		(*shell)->process_pid[i] = fork(); // fork 
		if ((*shell)->process_pid[i] == -1)
			print_sys_error(FAILED_FORK, NULL, shell);
		current_cmd = (*shell)->cmds[i];
		handle_cmd_redirection(shell, current_cmd);
		i++;
	}
	
}
