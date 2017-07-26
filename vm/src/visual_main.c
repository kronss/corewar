/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:08:06 by ochayche          #+#    #+#             */
/*   Updated: 2017/06/28 17:08:06 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			redraw_pc(t_data *data)
{
	t_proc		*proc;

	proc = data->processes;
	while (proc)
	{
		data->color[proc->pc] |= 0b00001000;
		proc = proc->next;
	}
}

static void		colored_byte(t_uchar i, t_uchar color, int y, int x)
{
	if (color == 5)
		attron(A_BOLD);
	attron(COLOR_PAIR(color));
	mvprintw(y, x, "%0.2hhx", i);
	attroff(COLOR_PAIR(color));
	if (color == 5)
		attroff(A_BOLD);
}

static void		print_map(t_data *data, int shift_y, int shift_x)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		colored_byte(data->map[i], data->color[i], i / 64 + shift_y,
												(i % 64) * 3 + shift_x);
		++i;
	}
}

void			show_map(t_data *data, t_viz *viz)
{
	print_map(data, 2, 3);
	attron(A_BOLD);
	print_dynamic_info(data, viz);
}

void			visual_main(t_data *data, t_viz *viz)
{
	show_map(data, viz);
	key_event(data, viz);
	attroff(A_BOLD);
}
