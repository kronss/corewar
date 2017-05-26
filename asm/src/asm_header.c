/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:41:36 by atrush            #+#    #+#             */
/*   Updated: 2017/05/26 15:41:39 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/corewar.h"

void syntax_error(unsigned int line, unsigned int column)
{
	ft_putstr_fd("Syntax error on [", 2);
	ft_putnbr_fd(line + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putstr_fd("]", 2);
	exit (-2);
}

void empty_line(char **line, unsigned int line_num, size_t n)
{
	char	*str;
	size_t 	i;

	i = 0;
	str = *line;
	while (str[i] && (i < n || n == 0))
	{
		if (ft_isspace(str[i]) == 0)
		{
			ft_strdel(line);
			syntax_error(line_num, (unsigned int)i);
		}
		i++;
	}
}

short int copy_cmd_text(char **line, t_header head, int type)
{
	size_t	start;
	char	*str;

	str = *line;
	start = ft_strlen(str) - ft_strlen(ft_strstr(str, 
		(type == 1 ? NAME_CMD_STRING : COMMENT_CMD_STRING)));
	empty_line(line, head.prog_size, start);
	ft_printf("lol");
	str += start + ft_strlen(type == 1 ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	while (ft_isspace(*str))
		str++;
	if (*str != '\"')
	{
		ft_strdel(line);
		syntax_error(head.prog_size, ft_strlen(*line) - ft_strlen(str) + 1);
	}
	return (type);
}

/*
** h_f (head_flag)
** 0 - empty
** 1 - name
** 2 - comment
** 3 - name + comment
*/

t_header make_header(int fd)
{
	t_header	head;
	char		*line;
	short int	h_f;

	line = NULL;
	head.magic = COREWAR_EXEC_MAGIC;
	head.prog_size = 0;
	h_f = 0;
	ft_bzero(head.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(head.comment, COMMENT_LENGTH + 1);
	while (get_next_line(fd, &line) == 1 && h_f != 3)
	{
		if ((h_f == 0 || h_f == 2) && ft_strstr(line, NAME_CMD_STRING))
			h_f += copy_cmd_text(&line, head, 1);
		else if ((h_f == 0 || h_f == 1) && ft_strstr(line, COMMENT_CMD_STRING))
			h_f += copy_cmd_text(&line, head, 2);
		else
			empty_line(&line, head.prog_size, 0);
		head.prog_size += 1;
	}
	return (head);
}
