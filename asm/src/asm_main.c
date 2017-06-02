/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:14:28 by atrush            #+#    #+#             */
/*   Updated: 2017/05/25 15:14:30 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/corewar.h"

static int	open_file(char *filename)
{
	int fd;

	errno = 0;
	fd = open(filename, O_RDONLY);
	if (errno != 0)
	{
		perror(filename);
		exit (-1);
	}
	return (fd);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_body		*body;
	t_header	head;

	if (argc > 1)
	{
		fd = open_file(argv[argc - 1]);
		head = make_header(fd);
		body = make_body(fd, head.prog_size);
		close(fd);	
	}
	else
		ft_printf("Usage: %s%s", argv[0], USAGE);
	return (0);
}
