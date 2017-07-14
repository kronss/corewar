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

#include "corewar.h"

int				empty(char *line)
{
	size_t	i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (ft_isspace(line[i]) == 0)
			{
				if (line[i] == COMMENT_CHAR || line[i] == SECOND_COMMENT_CHAR)
					return (-1);
				return (i);
			}
			i++;
		}
	}
	return (-1);
}

static void		handling_line(char **line)
{
	size_t	i;
	char	flag;
	
	if (!(*line))
		return ;
	i = 0;
	flag = 0;
	while ((*line)[i])
	{
		if (flag && (*line)[i] == SEPARATOR_CHAR)
			(*line)[i] = COMMENT_CHAR;
		else if ((*line)[i] == COMMENT_CHAR || (*line)[i] == SECOND_COMMENT_CHAR)
			flag = 1;
		i++;
	}
}

static int		search_data(char **line, t_body **root, t_asml asml[16])
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
	if (search_cmd(*line, &(tmp->cmd), &i, asml) == 0)
		return (i);
	if (tmp->cmd != -1)
	{
		handling_line(line);
		if ((res = search_args(*line, &tmp, &i, asml)) == -1)
			read_error(line, root);
		else if (res == 0)
			return (i);
	}
	return ((empty(*line + i) == -1) ? -1 : empty(*line + i) + (int)i);
}

static void		new_line(int fd, char **line, t_body **root)
{
	char	sym;
	
	ft_strdel(line);
	lseek(fd, -1, SEEK_CUR);
	if (read(fd, &sym, 1) != 1)
		read_error(line, root);
	if (sym != '\n')
	{
		body_delete(root);
		ft_putstr_fd("Syntax error - unexpected end of input ", 2);
		ft_putstr_fd("(Perhaps you forgot to end with a newline ?)\n", 2);
		exit(-12);
	}
}

t_body			*make_body(int fd, unsigned int line_num, t_asml asml[16])
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
			if ((result = search_data(&line, &root, asml)) >= 0)
				syntax_body_error(line_num, result, &line, &root);
		}
		line_num++;
	}
	new_line(fd, &line, &root);
	if (!root)
		empty_code();
	return (root);
}
