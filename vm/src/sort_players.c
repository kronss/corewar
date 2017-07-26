/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_players.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 17:51:50 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/29 17:52:37 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		initialize_visited(t_player *node, int visited[])
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		visited[i] = 0;
		++i;
	}
	while (node != NULL)
	{
		if (node->player_id != -1)
		{
			visited[node->player_id] = 1;
		}
		node = node->next;
	}
}

static void		providing_player_id(t_player *node, int visited[])
{
	int			i;

	while (node != NULL)
	{
		if (node->player_id == -1)
		{
			i = 0;
			while (i < MAX_PLAYERS)
			{
				if (visited[i] == 0)
				{
					node->player_id = i;
					visited[i] = 1;
					break ;
				}
				++i;
			}
		}
		node = node->next;
	}
}

static void		providing_real_player_id(t_player *node)
{
	int			i;

	i = -1;
	while (node != NULL)
	{
		node->player_id = i;
		--i;
		node = node->next;
	}
}

void			sort_players(t_data *data)
{
	int			visited[MAX_PLAYERS];

	initialize_visited(data->players, visited);
	providing_player_id(data->players, visited);
	sort_list(data);
	providing_real_player_id(data->players);
}
