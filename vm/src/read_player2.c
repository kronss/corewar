/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:02:39 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/07/04 18:02:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char		*cut_string(char *buf)
{
	char		*str;

	str = ft_strdup(buf);
	if (str == NULL)
	{
		return (NULL);
	}
	return (str);
}

char			*read_name(int fd)
{
	char		*buf;
	char		*name;
	ssize_t		err;

	buf = ft_strnew(PROG_NAME_LENGTH);
	if (buf == NULL)
	{
		return (NULL);
	}
	err = read(fd, buf, PROG_NAME_LENGTH);
	if (err == -1 || err != PROG_NAME_LENGTH)
	{
		ft_strdel(&buf);
		return (NULL);
	}
	lseek(fd, sizeof(char) * 4, SEEK_CUR);
	name = cut_string(buf);
	ft_strdel(&buf);
	return (name);
}

char			*read_comment(int fd)
{
	char		*buf;
	ssize_t		err;
	char		*comment;

	buf = ft_strnew(COMMENT_LENGTH);
	if (buf == NULL)
	{
		return (NULL);
	}
	err = read(fd, buf, COMMENT_LENGTH);
	if (err == -1 || err != COMMENT_LENGTH)
	{
		ft_strdel(&buf);
		return (NULL);
	}
	lseek(fd, sizeof(char) * 4, SEEK_CUR);
	comment = cut_string(buf);
	ft_strdel(&buf);
	return (comment);
}

char			*read_byte_code(int fd, int prog_size, char *str)
{
	int			err;
	char		*buf;

	buf = ft_strnew((size_t)prog_size + 1);
	err = read(fd, buf, prog_size + 1);
	if (err == -1)
	{
		ft_strdel(&buf);
	}
	else if (prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf(ERROR_SIZE2);
		ft_strdel(&buf);
	}
	else if (err != prog_size)
	{
		ft_strdel(&buf);
		ft_printf(ERROR_SIZE1, str);
	}
	return (buf);
}
