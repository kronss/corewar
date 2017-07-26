/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by abykov            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	shift_pc_on_map(t_data *data, t_proc *proc, int g_pc, int cmd)
{
	if (cmd != 8)
	{
		data->color[proc->pc] &= 0b11110111;
		if (data->asml[cmd].cod_oct == 1)
		{
			proc->pc = change_pc(g_pc);
		}
		else
		{
			proc->pc = change_pc(g_pc + data->asml[cmd].label_size);
		}
		data->color[proc->pc] |= 0b00001000;
	}
}

void	ressurection(t_player **player)
{
	t_player *tmp;

	tmp = *player;
	while (tmp)
	{
		tmp->lives_in_curr = 0;
		tmp = tmp->next;
	}
}

void	reduce_cycle_to_die(t_data *data)
{
	if (data->lives_in_curr >= NBR_LIVE)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->checks = 0;
	}
	else if (++(data->checks) >= MAX_CHECKS)
	{
		data->cycle_to_die -= CYCLE_DELTA;
		data->checks = 0;
	}
	if (data->cycle_to_die < 0)
		data->cycle_to_die = 0;
}
