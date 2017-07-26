/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:39:05 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:39:13 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	open_write_file(char *filename)
{
	int		fd;
	char	*s_file;

	s_file = filename;
	if ((s_file = ft_strnew(ft_strlen(filename) + 5)) == NULL)
	{
		perror("");
		return (-1);
	}
	ft_strcpy(s_file, "source_");
	ft_strncat(s_file, filename, ft_strlen(filename) - 3);
	ft_strcat(s_file, "s");
	fd = open(s_file, O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (errno != 0 || fd < 3)
	{
		ft_strdel(&s_file);
		perror(filename);
		return (-1);
	}
	ft_printf("%sCreating \"%s\" file...%s\n", YELLOW, s_file, DEFAULT);
	ft_strdel(&s_file);
	return (fd);
}

static int	without_opcode(int cor_fd, int s_fd, size_t size)
{
	int value;

	if (!read_int(cor_fd, &value, size))
		return (0);
	ft_putstr_fd(" ", s_fd);
	ft_putchar_fd(DIRECT_CHAR, s_fd);
	ft_putnbr_fd(value, s_fd);
	return ((int)size);
}

static int	decompilation(int cor_fd, int s_fd, t_asml asml[16])
{
	int size;
	int cmd;

	if ((size = read_header(cor_fd, s_fd)) <= 0)
		return (0);
	while (size > 0)
	{
		if (!read_int(cor_fd, &cmd, 1))
			return (0);
		if (cmd < 1 || cmd > 16)
			return (0);
		ft_putstr_fd("\t", s_fd);
		ft_putstr_fd(asml[cmd - 1].name, s_fd);
		if (asml[cmd - 1].cod_oct)
			cmd = with_opcode(cor_fd, s_fd, cmd - 1, asml) + 1;
		else
			cmd = without_opcode(cor_fd, s_fd, asml[cmd - 1].label_size);
		if (cmd == 0)
			return (0);
		ft_putstr_fd("\n", s_fd);
		size -= (cmd + 1);
	}
	if (size < 0 || read(cor_fd, &size, 1) != 0)
		return (0);
	return (1);
}

int			disasm(t_asml asml[16], int argc, char **argv)
{
	int	cor_fd;
	int s_fd;

	if (argc < 3 || ft_strcmp(argv[argc - 2], "-d") != 0)
		return (0);
	if (!argv[argc - 1] || ft_strlen(argv[argc - 1]) < 4 ||
		ft_strcmp(argv[argc - 1] + ft_strlen(argv[argc - 1]) - 4, ".cor") != 0)
	{
		ft_printf("%s -d : The file must have \".cor\" extension!%s\n",
			RED, DEFAULT);
		exit(-10);
	}
	cor_fd = open_read_file(argv[argc - 1]);
	s_fd = open_write_file(argv[argc - 1]);
	if (!decompilation(cor_fd, s_fd, asml))
	{
		close(cor_fd);
		close(s_fd);
		ft_printf("%sDecompilation error!%s\n", RED, DEFAULT);
		exit(-11);
	}
	close(cor_fd);
	close(s_fd);
	ft_printf("%sDecompilation was successful.%s\n", GREEN, DEFAULT);
	return (1);
}
