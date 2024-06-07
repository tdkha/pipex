/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:00:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/07 14:05:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	parser_scan(int ac, int cmd_index, char **av, t_cmd_parser *parser)
{
	if (ft_strnstr(av[cmd_index], "here_doc", ft_strlen("here_doc")))
		parser->here_doc = 1;
	else if (parser->here_doc == 0 && cmd_index == 1)
	{
		parser->in = 1;
		parser->redirect_file = av[cmd_index];
	}
	else if (parser->here_doc == 0 && cmd_index == ac - 2)
	{
		parser->out = 1;
		parser->redirect_file = av[cmd_index + 1];
	}
}

static void parser_init(t_cmd_parser *parser)
{
	parser->cmd = NULL;
	parser->split_cmd = NULL;
	parser->path = NULL;
	parser->here_doc = 0;
	parser->in = 0;
	parser->out = 0;
	parser->cmd_found = 0;
	parser->cmd_parse = 0;
	parser->redirect_file = NULL;
}

static void parser_reset(t_cmd_parser *parser)
{
	parser->cmd = NULL;
	parser->split_cmd = NULL;
	parser->path = NULL;
	parser->here_doc = 0;
	parser->in = 0;
	parser->out = 0;
	parser->cmd_found = 0;
	parser->redirect_file = NULL;
}

static inline void	parser_set(t_cmd_parser *parser, char **av, char **envp, t_shell **shell)
{
	char	**cmds;

	cmds = NULL;
	if (!parser->cmd)
		print_sys_error(FAILED_MALLOC, NULL, shell);
	cmds = ft_split(parser->cmd, ' ');
	if (!cmds)
		print_sys_error(FAILED_MALLOC, NULL, shell);
	parser->path = find_path(cmds[0], envp);
	parser->split_cmd = cmds;
	if (parser->path)
	{
		(*shell)->cmds[parser->cmd_parse] = cmd_init(parser, shell);
		parser_reset(parser);
		parser->cmd_parse++;
		if ((*shell)->cmds[parser->cmd_parse - 1] == NULL)
			return (free_shell(shell));
	} 
	else
	{
		free(parser->cmd);
		ft_multiple_free_set_null(cmds);
	}
}

void	parse_cmds(int ac, char **av, char **envp, t_shell **shell)
{
	
	int		i;
	t_cmd_parser parser;

	parser_init(&parser);
	for (i = 1; i <= ac - 1; i++) {
		parser_scan(ac, i, av, &parser);
		parser.cmd = ft_strtrim(av[i], " ");
		parser_set(&parser, av, envp, shell);
	}
}

