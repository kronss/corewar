/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork_fork_sti_st.c                                :+:      :+:    :+:   */
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
** lfork: Opcode 15. Same as a fork without modulo in the address.
*/

void			lfork(int args[4], t_proc *proc, t_data *data)
{
	t_proc		*temp;

	temp = create_proc(&data->processes);
	inheritance(temp->id, proc->id, data, args[0]);
}

/*
** T_DIR
** fork: Opcode 12. There is no argument’s coding byte, take an index.
** Create a new process that will inherit the different states of its father,
** except its PC, which will be put at (PC + (1st parameter % IDX_MOD)).
*/

void			ft_fork(int args[4], t_proc *proc, t_data *data)
{
	t_proc		*temp;

	temp = create_proc(&data->processes);
	inheritance(temp->id, proc->id, data, args[0] % IDX_MOD);
}

/*
** T_REG,   T_REG | T_DIR | T_IND,   T_DIR | T_REG
** sti: Opcode 11. Take a registry, and two indexes (potentially registries)
** add the two indexes, and use this result as an address where
** the value of the first parameter will be copied.
*/

void			sti(int args[4], t_proc *proc, t_data *data)
{
	int			a;
	int			b;
	int			c;

	a = proc->reg[args[0] - 1];
	b = get_arg((args[3] >> 4) & 3, proc, args[1], data->map);
	c = get_arg((args[3] >> 2) & 3, proc, args[2], data->map);
	write_4_bytes(data, proc, proc->pc + (b + c) % IDX_MOD, a);
}

/*
** T_REG,   T_IND | T_REG
** st: Opcode 03. Take a registry and a registry or an indirect and
** store the value of the registry toward a second argument.
** For example, st r1, 42 store the value of r1 at the
** address (PC + (42 % IDX_MOD))
*/

void			st(int args[4], t_proc *proc, t_data *data)
{
	int			a;
	int			b;

	a = proc->reg[args[0] - 1];
	if (((args[3] >> 4) & 3) == IND_CODE)
	{
		b = args[1];
		write_4_bytes(data, proc, proc->pc + (b % IDX_MOD), a);
	}
	else
	{
		proc->reg[args[1] - 1] = a;
	}
}
