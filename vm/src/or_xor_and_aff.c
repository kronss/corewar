/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor_and_aff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by abykov            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** T_REG | T_IND | T_DIR,   T_REG | T_IND | T_DIR,   T_REG
** or: Opcode 07. bit-to-bit OR, in the same spirit and principle of and.
*/

void		ft_or(int args[4], t_proc *proc, t_data *data)
{
	int		a;
	int		b;

	a = get_arg((args[3] >> 6) & 3, proc, args[0], data->map);
	b = get_arg((args[3] >> 4) & 3, proc, args[1], data->map);
	proc->reg[args[2] - 1] = a | b;
}

/*
** T_REG | T_IND | T_DIR,   T_REG | T_IND | T_DIR,   T_REG
** xor: Opcode 08. Acts like and with an exclusive OR.
*/

void		ft_xor(int args[4], t_proc *proc, t_data *data)
{
	int		a;
	int		b;

	a = get_arg((args[3] >> 6) & 3, proc, args[0], data->map);
	b = get_arg((args[3] >> 4) & 3, proc, args[1], data->map);
	proc->reg[args[2] - 1] = a ^ b;
}

/*
** T_REG | T_DIR | T_IND,    T_REG | T_IND | T_DIR,    T_REG
** and: Opcode 06.
** Apply an & (bit-to-bit AND) over the first two arguments and store the result
** in a registry, which is the third argument. Modifies the carry.
*/

void		ft_and(int args[4], t_proc *proc, t_data *data)
{
	int		a;
	int		b;

	a = get_arg((args[3] >> 6) & 3, proc, args[0], data->map);
	b = get_arg((args[3] >> 4) & 3, proc, args[1], data->map);
	proc->reg[args[2] - 1] = a & b;
}

/*
** T_REG
** aff: The opcode is 16. There is an argument’s coding byte,
** even if it’s a bit silly because there is only 1 argument that is a registry,
** which is a registry, and its content is interpreted by the character’s ASCII
** value to display on the standard output. The code is modulo 256.
*/

void		ft_aff(int args[4], t_proc *proc, t_data *data)
{
	if (data->visual_flag == 0)
		ft_printf("Aff: %c\n", proc->reg[args[0] - 1] % 256);
}
