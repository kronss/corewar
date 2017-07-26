/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 18:08:26 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/07/21 18:08:36 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		sort_else_norme(t_player **prev, t_player **tmp1)
{
	*prev = *tmp1;
	*tmp1 = (*tmp1)->next;
}

static void		sort_list_norme(t_data *data, t_player *tmp1,
								t_player *tmp2, t_player *prev)
{
	if (prev != NULL)
	{
		prev->next = tmp2;
		tmp1->next = tmp2->next;
		tmp2->next = tmp1;
	}
	else
	{
		tmp1->next = tmp2->next;
		tmp2->next = tmp1;
		data->players = tmp2;
	}
}

void			sort_list(t_data *data)
{
	t_player	*tmp1;
	t_player	*tmp2;
	t_player	*prev;
	int			i;

	i = 0;
	while (i < MAX_PLAYERS - 1)
	{
		tmp1 = data->players;
		prev = NULL;
		while (tmp1 != NULL && tmp1->next != NULL)
		{
			tmp2 = tmp1->next;
			if (tmp1->player_id > tmp2->player_id)
			{
				sort_list_norme(data, tmp1, tmp2, prev);
				prev = tmp2;
			}
			else
			{
				sort_else_norme(&prev, &tmp1);
			}
		}
		++i;
	}
}
