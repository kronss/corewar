/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_init_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 11:36:40 by ochayche          #+#    #+#             */
/*   Updated: 2017/07/01 11:36:41 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*who_is_win(t_player *tmp, int win_id)
{
	while (tmp)
	{
		if (win_id == tmp->player_id)
			return (tmp->name);
		tmp = tmp->next;
	}
	return (NULL);
}

void		destroy_window(t_data *data, t_viz *viz)
{
	int		winner;
	char	*str;

	winner = ft_abs(data->winner_id);
	str = who_is_win(data->players, data->winner_id);
	attron(A_BOLD);
	mvprintw(viz->y, viz->x, "The winner is : ");
	attron(COLOR_PAIR(winner));
	mvprintw(viz->y, viz->x + 16, "%s", str);
	attroff(COLOR_PAIR(winner));
	mvprintw(viz->y + 2, viz->x, "Press any key to finish");
	attroff(A_BOLD);
	nodelay(stdscr, FALSE);
	getch();
	endwin();
}

/*
** chanell	- color set
** 32 		- reset to std output
** 33 		- full black
** 34 		- border
**
** 1		- green player(-1)
** 2		- blue player(-2)
** 3		- red player(-3)
** 4		- cyan player(-4)
** 5		- unused byte
**
** 9		- green player(-1) + PC
** 10		- blue player(-2) + PC
** 11		- red player(-3) + PC
** 12		- cyan player(-4) + PC
** 13		- unused byte + PC
*/

void		create_color_pair(void)
{
	start_color();
	init_pair(32, COLOR_WHITE, COLOR_BLACK);
	init_pair(33, 16, 16);
	init_pair(34, 241, 241);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, 242, COLOR_BLACK);
	init_pair(9, COLOR_BLACK, COLOR_GREEN);
	init_pair(10, COLOR_BLACK, COLOR_BLUE);
	init_pair(11, COLOR_BLACK, COLOR_RED);
	init_pair(12, COLOR_BLACK, COLOR_CYAN);
	init_pair(13, 240, 240);
}

void		init_viz(t_viz *viz)
{
	viz->pause = 1;
	viz->hz = 50;
	ft_bzero(viz->abs_proportion, (MAX_PLAYERS) * sizeof(int));
	ft_bzero(viz->rel_proportion, (MAX_PLAYERS) * sizeof(int));
	viz->print_last = 0;
}

/*
** init_window()
** initialize new treminal window and show map
*/

void		init_window(t_data *data, t_viz *viz)
{
	init_viz(viz);
	initscr();
	curs_set(0);
	noecho();
	create_color_pair();
	print_border_box();
	show_map(data, viz);
	attron(A_BOLD);
	print_static_info(data, viz);
	pause_event(data, viz);
	attroff(A_BOLD);
}
