/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:14:28 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:35:37 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			open_read_file(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (errno != 0 || fd < 3)
	{
		perror(filename);
		exit(-1);
	}
	return (fd);
}

static int	open_write_file(char *filename, char *cor_file)
{
	int		fd;
	size_t	size;

	size = 0;
	while ((cor_file = ft_strchr(cor_file, '.')))
		size = ft_strlen(cor_file++);
	size = ft_strlen(filename) - size;
	if ((cor_file = ft_strnew(size + 4)) == NULL)
	{
		perror("");
		return (-1);
	}
	ft_strncpy(cor_file, filename, size);
	ft_strcat(cor_file, ".cor");
	fd = open(cor_file, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (errno != 0 || fd < 3)
	{
		ft_strdel(&cor_file);
		perror(filename);
		return (-1);
	}
	ft_printf("Writing output program to %s\n", cor_file);
	ft_strdel(&cor_file);
	return (fd);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_body		*body;
	t_header	head;
	t_asml		asml[16];

	if (argc > 1)
	{
		asml_default(asml);
		if (disasm(asml, argc, argv))
			return (0);
		fd = open_read_file(argv[argc - 1]);
		head = make_header(fd);
		body = make_body(fd, head.prog_size, asml);
		close(fd);
		head.prog_size = resize(&body, asml);
		if ((fd = open_write_file(argv[argc - 1], argv[argc - 1])) == -1)
			return (body_delete(&body));
		write_to_file(fd, head, &body, asml);
		close(fd);
		body_delete(&body);
	}
	else
		ft_printf("Usage: %s%s%s%s", argv[0], US1, US2, US3);
	return (0);
}
