/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 19:22:14 by ochayche          #+#    #+#             */
/*   Updated: 2017/06/05 19:22:15 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			ft_usage(t_data *data)
{
	ft_printf(USAGE);
	destruct(data);
	exit(1);
}

static void		invalid_players(t_data *data)
{
	if (data->players == NULL || data->processes == NULL)
	{
		ft_printf("There are no players or processes\n");
		destruct(data);
		exit(1);
	}
	if (data->num_of_players > MAX_PLAYERS)
	{
		ft_printf("The number of players exceeds the one in the header\n");
		destruct(data);
		exit(1);
	}
}

static void		introducing_players(t_data *data)
{
	t_player *node;

	ft_printf("Introducing contestants...\n");
	node = data->players;
	while (node != NULL)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			-1 * node->player_id, node->prog_size, node->name, node->comment);
		node = node->next;
	}
}

int				main(int argc, char **argv)
{
	t_data		data;

	if (argc > 1)
	{
		init_data(&data);
		read_args(&data, argv, argc);
		proc_init_basic(&data);
		invalid_players(&data);
		map_init(&data);
		introducing_players(&data);
		asml_default(data.asml);
		game_on(&data);
	}
	else
	{
		ft_usage(&data);
	}
	destruct(&data);
	return (0);
}
