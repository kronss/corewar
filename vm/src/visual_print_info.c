/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_print_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 16:07:09 by ochayche          #+#    #+#             */
/*   Updated: 2017/07/06 16:07:10 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_static_players(int *y, int x, t_player *player, t_uint num)
{
	int		color;

	while (num)
	{
		mvprintw(*y, x, "Player %-2d :", player->player_id);
		color = ft_abs(player->player_id);
		attron(COLOR_PAIR(color));
		mvprintw(*y, 211, "%.41s", player->name);
		attroff(COLOR_PAIR(color));
		*y += 1;
		mvprintw(*y, x + 2, "Last live :");
		*y += 1;
		mvprintw(*y, x + 2, "Lives in current period :");
		*y += 2;
		player = player->next;
		num--;
	}
}

void		print_dynamic_players(int *y, int x, t_player *player, t_uint num)
{
	while (num)
	{
		*y += 1;
		mvprintw(*y, x + 3, "%10u", player->last_live);
		*y += 1;
		mvprintw(*y, x + 5, "%8u", player->lives_in_curr);
		*y += 2;
		player = player->next;
		num--;
	}
}

void		print_dynamic_info(t_data *data, t_viz *viz)
{
	int		y;
	int		x;

	y = 4;
	x = 221;
	mvprintw(y, x, "%-4.0f", viz->hz);
	y += 3;
	mvprintw(y, x - 14, "%-20u", data->cycle);
	y += 2;
	mvprintw(y, x - 10, "%-20u", data->num_of_proc);
	y += 2;
	print_dynamic_players(&y, x, data->players, data->num_of_players);
	find_proportion(data, viz, &y);
	mvprintw(y, x - 7, "%-4d", data->cycle_to_die);
	y += 2;
	mvprintw(y, x - 8, "%-4d", CYCLE_DELTA);
	y += 2;
	mvprintw(y, x - 11, "%-4d", NBR_LIVE);
	y += 2;
	mvprintw(y, x - 9, "%-4d", MAX_CHECKS);
	y += 2;
}

void		print_static_info_add(t_viz *viz, int y, int x)
{
	y += 2;
	mvprintw(y, x, "CYCLE_TO_DIE :");
	y += 2;
	mvprintw(y, x, "CYCLE_DELTA :");
	y += 2;
	mvprintw(y, x, "NBR_LIVE :");
	y += 2;
	mvprintw(y, x, "MAX_CHECKS :");
	y += 2;
	viz->y = y;
	viz->x = x;
}

void		print_static_info(t_data *data, t_viz *viz)
{
	int		y;
	int		x;

	y = 4;
	x = 199;
	mvprintw(y, x, "Cycles/second limit :");
	y += 3;
	mvprintw(y, x, "Cycle :");
	y += 2;
	mvprintw(y, x, "Processes :");
	y += 2;
	print_static_players(&y, x, data->players, data->num_of_players);
	mvprintw(y, x, "Live breakdown for current period :");
	y += 1;
	attron(COLOR_PAIR(5));
	mvprintw(y, x, "[--------------------------------------------------]");
	attroff(COLOR_PAIR(5));
	y += 2;
	mvprintw(y, x, "Live breakdown for last period :");
	y += 1;
	attron(COLOR_PAIR(5));
	mvprintw(y, x, "[--------------------------------------------------]");
	attroff(COLOR_PAIR(5));
	print_static_info_add(viz, y, x);
}
