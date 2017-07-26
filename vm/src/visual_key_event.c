/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 20:33:33 by ochayche          #+#    #+#             */
/*   Updated: 2017/07/04 20:33:33 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define MSLEEP(msec) usleep(msec * 1000000.0)
#define SPACE 32
#define ESC 27

void		period_event(t_viz *viz)
{
	double	period;

	nodelay(stdscr, TRUE);
	attron(A_BOLD);
	mvprintw(2, 199, "%-13s", "** RUNNING **");
	attroff(A_BOLD);
	period = (1 / viz->hz);
	MSLEEP(period);
}

void		esc_event(t_data *data)
{
	endwin();
	destruct(data);
	exit(0);
}

void		pause_event(t_data *data, t_viz *viz)
{
	int key;

	while (viz->pause == 1)
	{
		nodelay(stdscr, FALSE);
		mvprintw(2, 199, "%-13s", "** PAUSED **");
		key = getch();
		if (key == SPACE)
			viz->pause ^= 1;
		else if (key == 's')
			break ;
		else if (key == 'q')
			viz->hz -= 10;
		else if (key == 'w')
			viz->hz -= 1;
		else if (key == 'e')
			viz->hz += 1;
		else if (key == 'r')
			viz->hz += 10;
		(key == ESC) ? esc_event(data) : 0;
		((int)viz->hz < 5) ? viz->hz = 5 : 0;
		((int)viz->hz > 1000) ? viz->hz = 1000 : 0;
		mvprintw(4, 221, "%-4.0f", viz->hz);
	}
	period_event(viz);
}

void		key_event(t_data *data, t_viz *viz)
{
	int key;

	key = getch();
	if (key == ERR)
		return (pause_event(data, viz));
	if (key == SPACE)
		viz->pause ^= 1;
	else if (key == 'q')
		viz->hz -= 10;
	else if (key == 'w')
		viz->hz -= 1;
	else if (key == 'e')
		viz->hz += 1;
	else if (key == 'r')
		viz->hz += 10;
	else if (key == ESC)
		esc_event(data);
	if ((int)viz->hz < 5)
		viz->hz = 5;
	if ((int)viz->hz > 1000)
		viz->hz = 1000;
	pause_event(data, viz);
}
