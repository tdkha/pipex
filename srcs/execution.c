/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:34:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/06 16:39:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_process_execute(t_shell **shell)
{
	
}

void	child_process_execute(t_shell **shell)
{
	
}

static void	shell_handle_cmd_type(t_shell **shell, t_cmd *current_cmd)
{

}

void	shell_execute_cmds(t_shell **shell)
{
	t_cmd	*current_cmd;
	int		i;

	i = 0;
	while (i < (*shell)->cmd_count)
	{
		if (pipe((*shell)->fds) == -1)
			print_sys_error(FAILED_PIPE, NULL, shell);
		(*shell)->process_pid[i] = fork();
		if ((*shell)->process_pid[i] == -1)
			print_sys_error(FAILED_FORK, NULL, shell);
		current_cmd = (*shell)->cmds[i];
		
		i++;
	}
	
}
