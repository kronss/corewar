/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_print_border.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 13:31:49 by ochayche          #+#    #+#             */
/*   Updated: 2017/07/01 13:31:49 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_horizontal_line(int y, int x, int x_limit)
{
	attron(COLOR_PAIR(34));
	while (x < x_limit)
	{
		mvprintw(y, x, "*");
		++x;
	}
	attroff(COLOR_PAIR(34));
}

void		print_vertikal_line(int y, int x, int y_limit)
{
	attron(COLOR_PAIR(34));
	while (y < y_limit)
	{
		mvprintw(y, x, "*");
		++y;
	}
	attroff(COLOR_PAIR(34));
}

void		print_border_box(void)
{
	print_horizontal_line(0, 0, 254);
	print_horizontal_line(67, 0, 254);
	print_vertikal_line(1, 0, 67);
	print_vertikal_line(1, 196, 67);
	print_vertikal_line(1, 253, 67);
}
