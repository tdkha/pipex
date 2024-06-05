/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:00:04 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/05 15:19:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	parser_scan(int ac, int cmd_index, char *str, t_cmd_parser *parser)
{
	if (ft_strnstr(str, "here_doc", ft_strlen("here_doc")))
		parser->here_doc = 1;
	else if (parser->here_doc == 0 && cmd_index == 1)
		parser->in = 1;
	else if (parser->here_doc == 0 && cmd_index == ac - 1)
		parser->out = 1;
}

static void parser_reset(t_cmd_parser *parser)
{
	parser->cmd = NULL;
	parser->here_doc = 0;
	parser->in = 0;
	parser->out = 0;
	parser->cmd_found = 0;
}

void parse_cmds(int ac, char **av, char **envp, t_shell **shell)
{
	char	**cmds;
    char	*path;
    int		i;
    int		j = -1;
    t_cmd_parser parser;

    parser_reset(&parser);
    for (i = 1; i < ac - 1; i++) {
        parser_scan(ac, i, av[i], &parser);
        parser.cmd = ft_strtrim(av[i], " ");
		cmds = ft_split(parser.cmd, ' ');
        path = find_path(cmds[0], envp);
        if (path) {
            j++;
            (*shell)->cmds[j] = cmd_init(parser.cmd, path, shell);
            if ((*shell)->cmds[j] == NULL) {
                free_shell(shell);
                return;
            }
            parser_reset(&parser);
        } 
		else
            free(parser.cmd);
		ft_multiple_free_set_null(cmds);
    }
}

