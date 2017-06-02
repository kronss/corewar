/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 15:11:33 by atrush            #+#    #+#             */
/*   Updated: 2017/05/31 15:11:35 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void empty_code(void)
{
	ft_putstr_fd("File does not have any instructions.\n", 2);
	exit (-6);
}

void syntax_error(unsigned int line_num, unsigned int column, char **line)
{
	ft_strdel(line);
	ft_putstr_fd("Syntax error on [", 2);
	ft_putnbr_fd(line_num + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit (-2);
}

void syntax_body_error(unsigned int line_num, unsigned int column,
	char **line, t_body **root)
{
	ft_strdel(line);
	body_delete(root);
	ft_putstr_fd("Syntax error on [", 2);
	ft_putnbr_fd(line_num + 1, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(column + 1, 2);
	ft_putstr_fd("]\n", 2);
	exit (-5);
}

void read_error(char **line, t_body **root)
{
	ft_strdel(line);
	body_delete(root);
	perror("");
	exit(-4);
}
