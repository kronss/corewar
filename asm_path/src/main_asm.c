/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:24:20 by ochayche          #+#    #+#             */
/*   Updated: 2017/05/18 15:24:21 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main_asm.h"

void		parsing_file(int fd)
{


}

void		error_asm(void *t_data, int error_code, char *str)
{
	error_code == -1 ? ft_printf("Can't read source file %s\n", str) : 0;
	error_code == -2 ? ft_printf("Can't close source file\n") : 0;

	exit(1);
}

void		ft_usage()
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>\n");
	ft_printf("    -a : Instead of creating a .cor file, outputs a stripped \
and annotated version of the code to the standard output\n");
	exit(0);
}

int			main(int ar, char **av)
{
	int fd;

	if (ar == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) == -1)
			error_asm(NULL, -1, av[1]);
		else
			parsing_file(fd);
	}
	else if (ar == 3)
	{ 
		if (!ft_strcmp("-a", av[1]))
		{
			if ((fd = open(av[2], O_RDONLY)) == -1)
				error_asm(NULL, -1, av[2]);
			else
				parsing_file(fd);
		}
	}
	else
		ft_usage();
	if (close(fd) == -1)
		error_asm(NULL, -2, 0);
	return (0);
}
