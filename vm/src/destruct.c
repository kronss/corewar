/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by ochayche          #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** exit(666) - not enought memory
** exit(1) - validation exit
*/

void		destruct_fail_malloc(t_data *data)
{
	destruct(data);
	exit(666);
}

void		free_one_player_node(t_player *node)
{
	if (node->name != NULL)
	{
		free(node->name);
		node->name = NULL;
	}
	if (node->comment != NULL)
	{
		free(node->comment);
		node->comment = NULL;
	}
	if (node->byte_code != NULL)
	{
		free(node->byte_code);
		node->byte_code = NULL;
	}
	free(node);
}

void		free_all_players(t_player **root)
{
	t_player *tmp;

	while (*root)
	{
		tmp = *root;
		*root = tmp->next;
		free_one_player_node(tmp);
	}
	*root = NULL;
}

void		destruct(t_data *data)
{
	if (data->map != NULL)
	{
		free(data->map);
		data->map = NULL;
	}
	if (data->color != NULL)
	{
		free(data->color);
		data->color = NULL;
	}
	if (data->players != NULL)
	{
		free_all_players(&data->players);
	}
	if (data->processes != NULL)
	{
		delete_every_proc(&data->processes);
	}
}
