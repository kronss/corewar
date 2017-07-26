/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_add_sub_zjmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by abykov            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** T_DIR
** live: Opcode 01. The instruction that allows a process to stay alive.
** It can also record that the player whose number is
** the argument is indeed alive. No argument’s coding byte.
** Oh and its only argument is on 4 bytes.
*/

void			live(int args[4], t_proc *proc, t_data *data)
{
	t_player	*player;

	proc->last_live = data->cycle + 1;
	player = data->players;
	data->lives_in_curr += 1;
	while (player && player->player_id != args[0])
		player = player->next;
	if (!player)
		return ;
	data->winner_id = player->player_id;
	player->lives_in_curr += 1;
	player->last_live = data->cycle;
}

/*
** T_REG,   T_REG,   T_REG
** add: Opcode 04. Take three registries, add the first two,
** and place the result in the third, right before modifying the carry.
*/

void			add(int args[4], t_proc *proc, t_data *data)
{
	if (data)
		;
	proc->reg[args[2] - 1] = proc->reg[args[0] - 1] + proc->reg[args[1] - 1];
}

/*
** T_REG,   T_REG,   T_REG
** sub: Opcode 05. Take three registries, sub the first two,
** and place the result in the third, right before modifying the carry
*/

void			sub(int args[4], t_proc *proc, t_data *data)
{
	if (data)
		;
	proc->reg[args[2] - 1] = proc->reg[args[0] - 1] - proc->reg[args[1] - 1];
}

/*
** T_DIR
** zjmp: Opcode 09. It will take an index and jump to this address if
** the carry is 1.
*/

void			zjmp(int args[4], t_proc *proc, t_data *data)
{
	if (proc->carry == 1)
	{
		data->color[proc->pc] &= 0b11110111;
		proc->pc = change_pc(proc->pc + (args[0] % IDX_MOD));
	}
	else
	{
		data->color[proc->pc] &= 0b11110111;
		proc->pc = change_pc(proc->pc + 3);
	}
}
