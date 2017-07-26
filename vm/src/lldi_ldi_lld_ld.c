/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi_ldi_lld_ld.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by abykov            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** T_REG | T_DIR | T_IND,   T_DIR | T_REG,   T_REG
** lldi: Opcode 14. Same as ldi, but does not apply any modulo to the addresses.
** It will however, modify the carry.
*/

void			lldi(int args[4], t_proc *proc, t_data *data)
{
	int			a;
	int			b;

	a = get_arg_noidx((args[3] >> 6) & 3, proc, args[0], data->map);
	b = get_arg_noidx((args[3] >> 4) & 3, proc, args[1], data->map);
	proc->reg[args[2] - 1] = read_4_bytes(data->map, proc->pc + a + b);
}

/*
** T_REG | T_DIR | T_IND,   T_DIR | T_REG,   T_REG
** ldi: Opcode 10. It will use 2 indexes and 1 registry, adding the
** first two, treating that like an address, reading a value of a
** registry’s size and putting it on the third.
*/

void			ldi(int args[4], t_proc *proc, t_data *data)
{
	int			a;
	int			b;

	a = get_arg((args[3] >> 6) & 3, proc, args[0], data->map) % IDX_MOD;
	b = get_arg((args[3] >> 4) & 3, proc, args[1], data->map) % IDX_MOD;
	proc->reg[args[2] - 1] = read_4_bytes(data->map,
											proc->pc + (a + b) % IDX_MOD);
}

/*
** T_DIR | T_IND,   T_REG
** lld: Opcode 13. Means long-load. It the same as ld,
** but without % IDX_MOD. Modify the carry.
*/

/*
** a >>= 16; // to imitate a bug from the standard ./corewar
** Replace line #69 By the command above
*/

void			lld(int args[4], t_proc *proc, t_data *data)
{
	int			a;

	if (((args[3] >> 6) & 3) == DIR_CODE)
		a = args[0];
	else
	{
		a = read_4_bytes(data->map, proc->pc + args[0]);
		a &= 0xffff;
	}
	proc->reg[args[1] - 1] = a;
}

/*
** T_DIR | T_IND,   T_REG
** ld: Opcode 2. Take a random argument and a registry. Load the value of the
** first argument in the registry. It will change the carry.
*/

void			ld(int args[4], t_proc *proc, t_data *data)
{
	int			a;

	if (((args[3] >> 6) & 3) == DIR_CODE)
		a = args[0];
	else
	{
		a = read_4_bytes(data->map, proc->pc + (args[0] % IDX_MOD));
	}
	proc->reg[args[1] - 1] = a;
}
