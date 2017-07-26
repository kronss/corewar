/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:39:21 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:39:26 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			read_int(int fd, int *value, size_t size)
{
	unsigned char	buf[5];
	int				i;
	int				flag;

	i = 0;
	flag = 0;
	while (i < 5)
		buf[i++] = 0;
	if (read(fd, buf, size) != (int)size)
		return (0);
	i = 0;
	*value = 0;
	if (buf[0] >= 128)
	{
		buf[0] -= 128;
		flag = 1;
	}
	while (i < (int)size)
		*value = *value * 256 + buf[i++];
	if (flag && size == 4)
		*value -= 2147483648;
	else if (flag)
		*value -= 32768;
	return (1);
}

static int	read_comment(int cor_fd, int s_fd)
{
	unsigned char	line[COMMENT_LENGTH + 1];
	int				num;
	int				prog_size;

	if (!read_int(cor_fd, &prog_size, 4))
		return (0);
	if (prog_size <= 0)
		return (0);
	num = 0;
	while (num <= COMMENT_LENGTH)
		line[num++] = 0;
	if (read(cor_fd, line, COMMENT_LENGTH) != COMMENT_LENGTH)
		return (0);
	ft_putstr_fd(COMMENT_CMD_STRING, s_fd);
	ft_putstr_fd(" \"", s_fd);
	ft_putstr_fd((char*)line, s_fd);
	ft_putstr_fd("\"\n\n", s_fd);
	if (!read_int(cor_fd, &num, 4))
		return (0);
	if (num != 0)
		return (0);
	return (prog_size);
}

int			read_header(int cor_fd, int s_fd)
{
	unsigned char	line[PROG_NAME_LENGTH + 1];
	int				num;

	num = 0;
	while (num <= PROG_NAME_LENGTH)
		line[num++] = 0;
	if (!read_int(cor_fd, &num, 4))
		return (0);
	if (num != COREWAR_EXEC_MAGIC)
		return (0);
	if (read(cor_fd, line, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		return (0);
	ft_putstr_fd(NAME_CMD_STRING, s_fd);
	ft_putstr_fd(" \"", s_fd);
	ft_putstr_fd((char*)line, s_fd);
	ft_putstr_fd("\"\n", s_fd);
	if (!read_int(cor_fd, &num, 4))
		return (0);
	if (num != 0)
		return (0);
	return (read_comment(cor_fd, s_fd));
}
