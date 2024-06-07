/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:35:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/07 14:09:52 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmd	*cmd_init(t_cmd_parser *parser, t_shell **shell)
{
	t_cmd			*res;
	char	*cmd;
	char	*path;

	cmd = parser->cmd;
	path = parser->path;
	res = (t_cmd *) malloc (sizeof(t_cmd));
	if (!res)
		print_error(FAILED_MALLOC, NULL, shell);
	res->cmd = cmd;
	res->split_cmd = parser->split_cmd;
	res->path = path;
	if (parser->here_doc)
		res->redirect.type = HEREDOC;
	else if (parser->in == 1)
	{
		res->redirect.type = IN;
		res->redirect.from.name = parser->redirect_file;
	}
	else if (parser->out == 1)
	{
		res->redirect.type = OUT;
		res->redirect.to.name = parser->redirect_file;
	}
	return (res);
}


t_shell *shell_init(int ac, char **av, char **envp)
{
	t_shell	*shell;
	int		i;

	i = 0;
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
        print_error(FAILED_MALLOC, NULL, &shell);
	shell->ac = ac;
	shell->av = av;
	shell->envp = envp;
	shell->error = NO_ERROR;
	shell->cmd_count = ac - 3;
	shell->process_pid = (pid_t *) malloc (sizeof(pid_t) * shell->cmd_count);
	if (!(shell->process_pid))
		print_error(FAILED_MALLOC, NULL, &shell);
	shell->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (shell->cmd_count + 1));
	if (!shell->cmds)
        print_error(FAILED_MALLOC, NULL, &shell);
	while (i <= shell->cmd_count)
	{
		shell->cmds[i] = NULL;
		i++;
	}
	parse_cmds(ac, av, envp, &shell);
	return (shell);
}

void free_shell(t_shell **shell)
{
	int	i;

	i = 0;
	if (shell && *shell)
	{
		if ((*shell)->cmds)
		{
			while (i < (*shell)->cmd_count)
			{
				if ((*shell)->cmds[i])
				{
					free((*shell)->cmds[i]->cmd);
					free((*shell)->cmds[i]->path);
					free((*shell)->cmds[i]);
                }
				i++;
			}
			free((*shell)->cmds);
		}
		if ((*shell)->process_pid)
			free((*shell)->process_pid);
		free(*shell);
		*shell = NULL;
	}
}
