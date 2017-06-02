/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_body.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 14:29:06 by atrush            #+#    #+#             */
/*   Updated: 2017/05/31 14:29:15 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/corewar.h"

int			empty(char *line)
{
	size_t	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (ft_isspace(line[i]) == 0)
			{
				if (line[i] == COMMENT_CHAR)
					return (-1);
				return (i);
			}
			i++;
		}
	}
	return (-1);
}

static int	search_data(char **line, t_body **root)
{
	t_body		*tmp;
	size_t		i;
	int			res;

	tmp = *root;
	while (tmp && tmp->next)
		tmp = tmp->next;
	i = 0;
	if ((res = search_label(*line, &(tmp->label), &i)) == -1)
		read_error(line, root);
	else if (res == 0)
		return (i);
	if (empty(*line + i) == -1)
		return (-1);
	if (search_cmd(*line, &(tmp->cmd), &i) == 0)
		return (i);
	if (tmp->cmd != 0)
	{
		if ((res = search_args(*line, &tmp, &i)) == -1)
			read_error(line, root);
		else if (res == 0)
			return (i);
	}
	return ((empty(*line + i) == -1) ? -1 : empty(*line + i) + i);
}

t_body		*make_body(int fd, unsigned int line_num)
{
	t_body		*root;
	char		*line;
	int			result;

	root = NULL;
	line = NULL;
	errno = 0;
	while ((result = get_next_line(fd, &line)) != 0)
	{
		if (result == -1)
			read_error(&line, &root);
		if (empty(line) != -1)
		{
			if (!body_create(&root))
				read_error(&line, &root);	
			if ((result = search_data(&line, &root)) >= 0)
				syntax_body_error(line_num, result, &line, &root);
		}
		line_num++;
	}
	ft_strdel(&line);
	if (!root)
		empty_code();
	return (root);
}
