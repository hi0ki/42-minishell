/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hime <mel-hime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 23:59:24 by eel-ansa          #+#    #+#             */
/*   Updated: 2024/08/23 15:41:01 by mel-hime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_lexer	*get_node(char *line, int i, int index, int type)
{
	char		*str;
	static int	helper;
	t_lexer		*node;

	str = NULL;
	if (type == 0)
		str = ft_str_alloc(line + i, index);
	else if (type == 1)
	{
		if (line[i] == '\'')
			helper = SQUOTE;
		else if (line[i] == '\"')
			helper = DQUOTE;
		str = ft_str_alloc(line + i + 1, index - 1);
		node = lexer_lstnew(str);
		node->type = helper;
		if (line[index + i] != '\'' && line[index + i] != '\"')
			node->error_quotes = -1;
		return (node);
	}
	else if (type == 2)
		str = alloc_special_char(line + i);
	node = lexer_lstnew(str);
	set_type(&node);
	return (node);
}

static t_lexer	*handle_word(t_lexer *head, char *line, int *i)
{
	int	index;

	index = get_index(line + *i, " \t\"'><|");
	if (index != 0)
	{
		lexer_add_back(&head, get_node(line, *i, index, 0));
		*i += index;
	}
	return (head);
}

static t_lexer	*handle_quote( t_lexer *head, char *line, int *i)
{
	int	nbr;

	nbr = ft_handle_quotes(line + *i);
	lexer_add_back(&head, get_node(line, *i, nbr, 1));
	*i += nbr + 1;
	return (head);
}

static t_lexer	*handle_special_char(t_lexer *head, char *line, int *i)
{
	int	nbr;

	nbr = check_special_char(line + *i);
	lexer_add_back(&head, get_node(line, *i, 0, 2));
	*i += nbr;
	if (line[*i - nbr] != ' ')
		return (head);
	while (line[*i] == ' ')
		(*i)++;
	return (head);
}

t_lexer	*start_lexer(t_lexer *head, char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	head = NULL;
	tmp = line;
	line = ft_strtrim(line, " \t");
	free(tmp);
	while (line[i])
	{
		if (get_index(line + i, " \t\"'><|") != 0)
			head = handle_word(head, line, &i);
		else if (check_special_char(line + i) == 3)
		{
			head = handle_quote(head, line, &i);
		}
		else if (check_special_char(line + i) > 0)
			head = handle_special_char(head, line, &i);
	}
	free(line);
	return (head);
}
