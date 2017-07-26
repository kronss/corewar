/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:02:56 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/07/04 18:03:04 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_uint			big_to_little_endian(t_uint n)
{
	t_uint		res;

	res = 0;
	res = res | (n >> 24);
	res = res & 255;
	res = res | ((n >> 8) & 65280);
	res = res | (n << 24);
	res = res | ((n << 8) & 16711680);
	return (res);
}

int				check_magic(int fd)
{
	ssize_t		err;
	t_uint		magic;

	err = read(fd, &magic, 4);
	if (err == -1 || err != 4)
	{
		return (0);
	}
	magic = big_to_little_endian(magic);
	if (magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("Invalid magic number\n");
		return (0);
	}
	return (1);
}

int				read_size(int fd)
{
	int			prog_size;
	int			err;

	err = read(fd, &prog_size, 4);
	if (err == -1 || err != 4)
	{
		return (-1);
	}
	prog_size = big_to_little_endian(prog_size);
	return (prog_size);
}
