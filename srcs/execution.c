/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:34:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/07 15:47:00 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process_execute(t_shell **shell, t_cmd *current_cmd)
{
	if (current_cmd->redirect.type != HEREDOC)
	{
		execve(current_cmd->path, current_cmd->split_cmd, (*shell)->envp);
		print_error(FAILED_EXECVE, "execve_error", shell);
	}
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
		current_cmd->redirect.to.fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		fd_file_open = current_cmd->redirect.to.fd;
	}
	if (fd_file_open == -1 && access(filename, F_OK))
		print_error(NO_FILE_OR_DIRECTORY, filename, shell);
	else if (fd_file_open == -1 && !access(filename, F_OK))
		print_error(NO_PERMISSION, filename, shell);
	return (fd_file_open);
}

static inline void	handle_dup_and_close(
	t_shell **shell,
	t_cmd *current_cmd,
	t_redirect_type type,
	int	current_index
)
{
	if (type == IN)
	{
		if ((*shell)->process_pid[current_index] == 0)
		{
			printf("\033[0;31mDup and close\033[0m in CHILD with type IN\n");
			close((*shell)->fds[OUTPUT]); // Close write end of the pipe in child
			
			dup2(current_cmd->redirect.from.fd, STDIN_FILENO); // Redirect input
			close(current_cmd->redirect.from.fd);
			
			dup2((*shell)->fds[INPUT], STDOUT_FILENO); // Redirect output to pipe
			close((*shell)->fds[INPUT]);
		}
		else
		{
			printf("\033[0;31mDup and close\033[0m in PARENT with type IN\n");
			close((*shell)->fds[INPUT]); // Close read end of the pipe in parent
		}
	}
	else if (type == OUT)
	{
		if ((*shell)->process_pid[current_index] == 0)
		{
			printf("\033[0;31mDup and close\033[0m in CHILD with type OUT\n");
			close((*shell)->fds[INPUT]); // Close read end of the pipe in child
			
			dup2((*shell)->fds[OUTPUT], STDIN_FILENO); // Redirect input from pipe
			close((*shell)->fds[OUTPUT]);

			dup2(current_cmd->redirect.to.fd, STDOUT_FILENO); // Redirect output
			close(current_cmd->redirect.to.fd);
		}
		else
		{
			printf("\033[0;31mDup and close\033[0m in PARENT with type IN\n");
			close((*shell)->fds[OUTPUT]); // Close write end of the pipe in parent
		}
	}
}

static inline void	handle_cmd_redirection(
	t_shell **shell,
	t_cmd *current_cmd,
	int	current_index
)
{
	t_redirect_type	type;
	char			*filename;
	int				fd_file_open;

	type = current_cmd->redirect.type;
	if (type == IN || type == OUT)
	{
		handle_open(shell, current_cmd, type);
		handle_dup_and_close(shell, current_cmd, type, current_index);
	}
}

void	shell_execute_cmds(t_shell **shell)
{
	t_cmd	*current_cmd;
	pid_t	current_pid;
	int		i;

	i = 0;
	while (i < 1)
	{
		if (pipe((*shell)->fds) == -1) // pipe()
			print_sys_error(FAILED_PIPE, NULL, shell);
		(*shell)->process_pid[i] = fork(); // fork()
		if ((*shell)->process_pid[i] == -1)
			print_sys_error(FAILED_FORK, NULL, shell);
		current_pid = (*shell)->process_pid[i];
		current_cmd = (*shell)->cmds[i];
		handle_cmd_redirection(shell, current_cmd, i);
		if (current_pid == 0)
		{
			child_process_execute(shell, current_cmd);
		}
		i++;
	}
	i = 0;
	while (i < 1)
	{
		waitpid((*shell)->process_pid[i], NULL, 0);
		i++;
	}
}
