/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:32:25 by ochayche          #+#    #+#             */
/*   Updated: 2017/06/07 11:32:26 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			init_data(t_data *data)
{
	data->dump_arg = -2;
	data->map = NULL;
	data->color = NULL;
	data->cycle = 0;
	data->cycle_to_die = CYCLE_TO_DIE;
	data->checks = 0;
	data->last_check = 0;
	data->lives_in_curr = 0;
	data->num_of_players = 0;
	data->num_of_proc = 0;
	data->players = NULL;
	data->processes = NULL;
	data->visual_flag = 0;
}

void			map_init(t_data *data)
{
	t_player	*curr;
	int			i;
	int			j;

	data->map = (t_uchar *)malloc(sizeof(t_uchar) * (MEM_SIZE));
	data->color = (t_uchar *)malloc(sizeof(t_uchar) * (MEM_SIZE));
	if (data->map == NULL || data->color == NULL)
		destruct_fail_malloc(data);
	ft_bzero(data->map, MEM_SIZE);
	ft_memset(data->color, 5, MEM_SIZE);
	curr = data->players;
	i = 0;
	while (curr)
	{
		ft_memcpy(data->map + i, curr->byte_code, curr->prog_size);
		j = i;
		while (j < i + curr->prog_size)
		{
			data->color[j] = i / (MEM_SIZE / data->num_of_players) + 1;
			j++;
		}
		data->color[i] += 8;
		curr = curr->next;
		i += (MEM_SIZE / data->num_of_players);
	}
}

void			proc_init_basic(t_data *data)
{
	t_proc		*proc;
	t_player	*i;
	int			pc;

	i = data->players;
	pc = 0;
	while (i)
	{
		if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
			destruct_fail_malloc(data);
		proc->id = generate_id(data->processes);
		proc->player_id = i->player_id;
		proc->pc = pc;
		proc->last_live = 0;
		proc->cycles_to_exec = -1;
		ft_bzero(proc->reg, sizeof(int) * REG_NUMBER);
		proc->reg[0] = i->player_id;
		proc->carry = 0;
		proc->next = data->processes;
		data->processes = proc;
		i = i->next;
		pc += MEM_SIZE / data->num_of_players;
		data->winner_id = proc->player_id;
		data->num_of_proc += 1;
	}
}
