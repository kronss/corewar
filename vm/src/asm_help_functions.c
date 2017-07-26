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

int		read_4_bytes(t_uchar *map, int index)
{
	int	res;
	int	temp;

	res = 0;
	temp = 0;
	temp = map[change_pc(index + 0)];
	temp <<= 24;
	res |= temp;
	temp = map[change_pc(index + 1)];
	temp <<= 16;
	res |= temp;
	temp = map[change_pc(index + 2)];
	temp <<= 8;
	res |= temp;
	temp = map[change_pc(index + 3)];
	res |= temp;
	return (res);
}

void	write_4_bytes(t_data *data, t_proc *proc, int index, int var)
{
	int	pc;

	data->map[change_pc(index + 0)] = (var & 0xff000000) >> 24;
	data->map[change_pc(index + 1)] = (var & 0xff0000) >> 16;
	data->map[change_pc(index + 2)] = (var & 0xff00) >> 8;
	data->map[change_pc(index + 3)] = var & 0xff;
	pc = data->color[change_pc(index + 0)] & 0b00001000;
	data->color[change_pc(index + 0)] = (proc->player_id * (-1)) | pc;
	pc = data->color[change_pc(index + 1)] & 0b00001000;
	data->color[change_pc(index + 1)] = (proc->player_id * (-1)) | pc;
	pc = data->color[change_pc(index + 2)] & 0b00001000;
	data->color[change_pc(index + 2)] = (proc->player_id * (-1)) | pc;
	pc = data->color[change_pc(index + 3)] & 0b00001000;
	data->color[change_pc(index + 3)] = (proc->player_id * (-1)) | pc;
}

int		get_arg(char bin_code, t_proc *proc, int arg, t_uchar *map)
{
	if (bin_code == REG_CODE)
	{
		return (proc->reg[arg - 1]);
	}
	else if (bin_code == IND_CODE)
	{
		return (read_4_bytes(map, proc->pc + (arg % IDX_MOD)));
	}
	else
	{
		return (arg);
	}
}

int		get_arg_noidx(char bin_code, t_proc *proc, int arg, t_uchar *map)
{
	if (bin_code == REG_CODE)
	{
		return (proc->reg[arg - 1]);
	}
	else if (bin_code == IND_CODE)
	{
		return (read_4_bytes(map, proc->pc + arg));
	}
	else
	{
		return (arg);
	}
}

int		is_valid_reg(int reg)
{
	if (1 <= reg && reg <= 16)
		return (1);
	return (0);
}
