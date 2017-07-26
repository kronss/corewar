/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor_and_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by atrush            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				read_int(t_data *data, int pc, size_t size)
{
	int	i;
	int	num;
	int flag;

	i = 0;
	num = 0;
	flag = (data->map[change_pc(pc)] > 127 && size != 1) ? 1 : 0;
	while (i < (int)size)
	{
		if (flag && i == 0)
			num = data->map[change_pc(pc)] - 128;
		else
			num = num * 256 + data->map[change_pc(pc + i)];
		i++;
	}
	if (flag && size == 4)
		num -= 2147483648;
	else if (flag)
		num -= 32768;
	return (num);
}

static void		time_to_check(t_data *data)
{
	t_proc	*tmp;
	t_proc	*next;

	tmp = data->processes;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->last_live + data->cycle_to_die <= data->cycle)
		{
			data->color[tmp->pc] &= 0b11110111;
			delete_proc_by_id(tmp->id, &(data->processes));
			data->num_of_proc -= 1;
		}
		tmp = next;
	}
	reduce_cycle_to_die(data);
	data->last_check = data->cycle;
	data->lives_in_curr = 0;
	ressurection(&(data->players));
}

static void		do_i_have_the_right(t_proc **tmp, t_data *data)
{
	int cmd;

	cmd = read_int(data, (*tmp)->pc, 1);
	if ((*tmp)->cycles_to_exec == 0)
	{
		handling_args((*tmp)->cmd - 1, tmp, data);
		(*tmp)->cycles_to_exec -= 1;
	}
	else if ((*tmp)->cycles_to_exec == -1)
	{
		if (cmd < 1 || 16 < cmd)
		{
			data->color[(*tmp)->pc] &= 0b11110111;
			(*tmp)->pc = change_pc((*tmp)->pc + 1);
			data->color[(*tmp)->pc] |= 0b00001000;
			return ;
		}
		(*tmp)->cycles_to_exec = data->asml[cmd - 1].cycles - 2;
		(*tmp)->cmd = cmd;
	}
	else
		(*tmp)->cycles_to_exec -= 1;
}

static void		and_the_winner_is(t_data *data)
{
	t_player	*winner;

	winner = data->players;
	while (winner && winner->player_id != data->winner_id)
		winner = winner->next;
	ft_printf("Contestant %d, \"%s\", has won !\n",
		-1 * winner->player_id, winner->name);
}

void			game_on(t_data *data)
{
	t_proc		*tmp;
	t_viz		viz;

	(data->visual_flag) ? init_window(data, &viz) : 0;
	while (data->processes && data->cycle != data->dump_arg)
	{
		data->cycle += 1;
		tmp = data->processes;
		while (tmp)
		{
			do_i_have_the_right(&tmp, data);
			tmp = tmp->next;
		}
		if (data->cycle - data->last_check >= (t_uint)data->cycle_to_die)
		{
			time_to_check(data);
			viz.print_last = 1;
		}
		redraw_pc(data);
		(data->visual_flag) ? visual_main(data, &viz) : 0;
	}
	if (data->cycle == data->dump_arg)
		return (dump(data));
	(data->visual_flag) ? destroy_window(data, &viz) : 0;
	and_the_winner_is(data);
}
