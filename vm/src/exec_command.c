/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by abykov            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	change_carry(int cmd, t_proc *proc, int args[4], t_data *data)
{
	int		regi;

	regi = data->asml[cmd].arg_num - 1;
	if (proc->reg[args[regi] - 1] == 0)
	{
		proc->carry = 1;
	}
	else
	{
		proc->carry = 0;
	}
}

static void	exec_command2(int cmd, int args[4], t_proc *proc, t_data *data)
{
	if (cmd == 8)
		zjmp(args, proc, data);
	else if (cmd == 9)
		ldi(args, proc, data);
	else if (cmd == 10)
		sti(args, proc, data);
	else if (cmd == 11)
		ft_fork(args, proc, data);
	else if (cmd == 12)
		lld(args, proc, data);
	else if (cmd == 13)
		lldi(args, proc, data);
	else if (cmd == 14)
		lfork(args, proc, data);
	else if (cmd == 15)
		ft_aff(args, proc, data);
}

/*
** if argument is T_REG, but not valid, then skip command and args
*/

void		exec_command(int cmd, int args[4], t_proc *proc, t_data *data)
{
	if (((((args[3] >> 6) & 3) == REG_CODE) && !is_valid_reg(args[0]))
		|| ((((args[3] >> 4) & 3) == REG_CODE) && !is_valid_reg(args[1]))
		|| ((((args[3] >> 2) & 3) == REG_CODE) && !is_valid_reg(args[2])))
		return ;
	if (cmd == 0)
		live(args, proc, data);
	else if (cmd == 1)
		ld(args, proc, data);
	else if (cmd == 2)
		st(args, proc, data);
	else if (cmd == 3)
		add(args, proc, data);
	else if (cmd == 4)
		sub(args, proc, data);
	else if (cmd == 5)
		ft_and(args, proc, data);
	else if (cmd == 6)
		ft_or(args, proc, data);
	else if (cmd == 7)
		ft_xor(args, proc, data);
	else
		exec_command2(cmd, args, proc, data);
	if (data->asml[cmd].carry == 1)
		change_carry(cmd, proc, args, data);
}
