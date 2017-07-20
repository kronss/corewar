/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:11:33 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:34:51 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		inv_arg(char *name, short arg_num, char ***mas)
{
	free_char_mas(mas);
	ft_putstr_fd("Operation \'", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\' must have ", 2);
	ft_putnbr_fd(arg_num, 2);
	ft_putstr_fd(" arguments! ", 2);
	return (0);
}

void	empty_code(void)
{
	ft_putstr_fd("File does not have any instructions.\n", 2);
	exit(-6);
}

void	syntax_error(unsigned int line_num, unsigned int column, char **line)
{
	ft_strdel(line);
	ft_putstr_fd("Lexical or syntax error on [", 2);
	ft_putnbr_fd(line_num + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit(-2);
}

void	syntax_body_error(unsigned int line_num, unsigned int column,
		char **line, t_body **root)
{
	ft_strdel(line);
	body_delete(root);
	ft_putstr_fd("Lexical or syntax error on [", 2);
	ft_putnbr_fd(line_num + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit(-5);
}

void	read_error(char **line, t_body **root)
{
	ft_strdel(line);
	body_delete(root);
	perror("");
	exit(-4);
}
