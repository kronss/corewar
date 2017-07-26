/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_print_proportion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 17:15:21 by ochayche          #+#    #+#             */
/*   Updated: 2017/07/14 17:15:22 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define PROPORTION "--------------------------------------------------"

int			find_abs_result(t_player *tmp, t_uint *abs_proportion)
{
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	while (tmp != NULL)
	{
		abs_proportion[i] = tmp->lives_in_curr;
		sum += tmp->lives_in_curr;
		tmp = tmp->next;
		++i;
	}
	return (sum);
}

int			check_rel_result(t_uint *rel_proportion, int abs_lives,
										t_uint *abs_proportion, int max_player)
{
	int		i;

	i = 0;
	if (abs_lives == 0)
		return (0);
	while (i < max_player)
	{
		rel_proportion[i] = (abs_proportion[i] * 50) / abs_lives;
		++i;
	}
	return (1);
}

void		print_last(t_viz *viz, int *y)
{
	int		i;
	int		shift;

	i = 0;
	shift = 0;
	*y += 4;
	while (i < MAX_PLAYERS)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(*y, 200 + shift, "%.*s", viz->rel_proportion[i], PROPORTION);
		shift += viz->rel_proportion[i];
		attroff(COLOR_PAIR(i + 1));
		++i;
	}
	if (shift > 0)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(*y, 200 + shift, "%.*s", 50 - shift, PROPORTION);
		attroff(COLOR_PAIR(i + 1));
	}
	*y -= 4;
	attron(COLOR_PAIR(5));
	mvprintw(*y + 1, 200, "%s", PROPORTION);
	attroff(COLOR_PAIR(5));
}

void		print_current(t_viz *viz, int *y)
{
	int		i;
	int		shift;

	i = 0;
	shift = 0;
	*y += 1;
	while (i < MAX_PLAYERS)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(*y, 200 + shift, "%.*s", viz->rel_proportion[i], PROPORTION);
		shift += viz->rel_proportion[i];
		attroff(COLOR_PAIR(i + 1));
		++i;
	}
	if (shift > 0)
	{
		attron(COLOR_PAIR(i + 1));
		mvprintw(*y, 200 + shift, "%.*s", 50 - shift, PROPORTION);
		attroff(COLOR_PAIR(i + 1));
	}
	*y -= 1;
}

void		find_proportion(t_data *data, t_viz *viz, int *y)
{
	t_uint	max_player;

	max_player = data->num_of_players;
	viz->abs_lives = find_abs_result(data->players, viz->abs_proportion);
	if (viz->print_last)
	{
		print_last(viz, y);
		viz->abs_lives = 0;
		ft_bzero(viz->abs_proportion, (MAX_PLAYERS) * sizeof(int));
		ft_bzero(viz->rel_proportion, (MAX_PLAYERS) * sizeof(int));
		viz->print_last = 0;
	}
	if (check_rel_result(viz->rel_proportion, viz->abs_lives,
											viz->abs_proportion, max_player))
	{
		print_current(viz, y);
	}
	*y += 6;
}
