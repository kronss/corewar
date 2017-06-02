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

#include "corewar.h"

static void			empty_line(char **line, unsigned int line_num,
					int n, size_t i)
{
	char	*str;

	str = *line;
	while (str[i] && (i < (size_t)n || n == -1))
	{
		if (ft_isspace(str[i]) == 0)
		{
			if (str[i] == COMMENT_CHAR)
				return ;
			syntax_error(line_num, (unsigned int)i, line);
		}
		i++;
	}
}

static void			check_length(char **line, t_header *head,
					int type, size_t i)
{
	char	*str;
	size_t	size;
	size_t	length;

	str = (type == 1) ? &(((*head).prog_name)[0]) : &(((*head).comment)[0]);
	length = (type == 1) ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	size = ft_strlen(*line + i) - ft_strlen(ft_strchr(*line + i, '\"'));
	if (!ft_strchr(*line + i, '\"'))
		size++;
	if (ft_strlen(str) + size <= length)
		return ;
	if (type == 1)
		ft_putstr_fd("Champion name", 2);
	else
		ft_putstr_fd("Champion comment", 2);
	ft_putstr_fd(" too long (Max length ", 2);
	if (type == 1)
		ft_putnbr_fd(PROG_NAME_LENGTH, 2);
	else
		ft_putnbr_fd(COMMENT_LENGTH, 2);
	ft_putstr_fd(")\n", 2);
	ft_strdel(line);
	exit(-3);
}

static void			write_to_s_header(char **line, t_header *head,
					int type, int fd)
{
	char	*str;
	size_t	size;
	size_t	i;

	str = (type == 1) ? &(((*head).prog_name)[0]) : &(((*head).comment)[0]);
	i = ft_strlen(*line) - ft_strlen(ft_strchr(*line, '\"')) + 1;
	while (42)
	{
		size = ft_strlen(*line + i) - ft_strlen(ft_strchr(*line + i, '\"'));
		check_length(line, head, type, i);
		str = ft_strncat(str, *line + i, size);
		if (ft_strchr(*line + i, '\"'))
		{
			empty_line(line, (*head).prog_size, -1, size + i + 1);
			return ;
		}
		if (get_next_line(fd, line) != 1)
			syntax_error((*head).prog_size, 0, line);
		str = ft_strcat(str, "\n");
		(*head).prog_size += 1;
		i = 0;
	}
}

static short int	copy_cmd_text(char **line, t_header *head,
					int type, int fd)
{
	size_t	start;
	char	*str;

	str = *line;
	start = ft_strlen(str) - ft_strlen(ft_strstr(str,
		(type == 1 ? NAME_CMD_STRING : COMMENT_CMD_STRING)));
	empty_line(line, (*head).prog_size, start, 0);
	str += start + ft_strlen(type == 1 ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	while (ft_isspace(*str))
		str++;
	if (*str != '\"')
		syntax_error((*head).prog_size,
			ft_strlen(*line) - ft_strlen(str), line);
	write_to_s_header(line, head, type, fd);
	return (type);
}

/*
** h_f (head_flag)
** 0 - empty
** 1 - name
** 2 - comment
** 3 - name + comment
*/

t_header			make_header(int fd)
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
	while (h_f != 3 && get_next_line(fd, &line) == 1)
	{
		if ((h_f == 0 || h_f == 2) && ft_strstr(line, NAME_CMD_STRING))
			h_f += copy_cmd_text(&line, &head, 1, fd);
		else if ((h_f == 0 || h_f == 1) && ft_strstr(line, COMMENT_CMD_STRING))
			h_f += copy_cmd_text(&line, &head, 2, fd);
		else
			empty_line(&line, head.prog_size, -1, 0);
		head.prog_size += 1;
	}
	if (h_f != 3)
		syntax_error(head.prog_size, 0, &line);
	ft_strdel(&line);
	return (head);
}
