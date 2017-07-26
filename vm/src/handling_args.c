/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:34:13 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/07/21 16:42:03 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				g_acb;
int				g_pc;
int				g_args[4];

t_uint			change_pc(t_uint pc)
{
	return (pc % MEM_SIZE);
}

static int		first_arg(int cmd, t_data *data)
{
	int			ret;

	ret = 1;
	if (((g_acb >> 6) & 3) == REG_CODE && data->asml[cmd].arg_type & 256)
		g_args[0] = read_int(data, g_pc, REG_SIZE);
	else if (((g_acb >> 6) & 3) == DIR_CODE && data->asml[cmd].arg_type & 128)
		g_args[0] = read_int(data, g_pc, data->asml[cmd].label_size);
	else if (((g_acb >> 6) & 3) == IND_CODE && data->asml[cmd].arg_type & 64)
		g_args[0] = read_int(data, g_pc, IND_SIZE);
	else
		ret = 0;
	if (((g_acb >> 6) & 3) == REG_CODE)
		g_pc = change_pc(g_pc + REG_SIZE);
	else if (((g_acb >> 6) & 3) == DIR_CODE)
		g_pc = change_pc(g_pc + data->asml[cmd].label_size);
	else if (((g_acb >> 6) & 3) == IND_CODE)
		g_pc = change_pc(g_pc + IND_SIZE);
	return (ret);
}

static int		second_arg(int cmd, t_data *data)
{
	int			ret;

	ret = 1;
	if (data->asml[cmd].arg_num < 2 && ((g_acb >> 4) & 3) == 0)
		return (1);
	if (((g_acb >> 4) & 3) == REG_CODE && data->asml[cmd].arg_type & 32)
		g_args[1] = read_int(data, g_pc, REG_SIZE);
	else if (((g_acb >> 4) & 3) == DIR_CODE && data->asml[cmd].arg_type & 16)
		g_args[1] = read_int(data, g_pc, data->asml[cmd].label_size);
	else if (((g_acb >> 4) & 3) == IND_CODE && data->asml[cmd].arg_type & 8)
		g_args[1] = read_int(data, g_pc, IND_SIZE);
	else
		ret = 0;
	if (((g_acb >> 4) & 3) == REG_CODE)
		g_pc = change_pc(g_pc + REG_SIZE);
	else if (((g_acb >> 4) & 3) == DIR_CODE)
		g_pc = change_pc(g_pc + data->asml[cmd].label_size);
	else if (((g_acb >> 4) & 3) == IND_CODE)
		g_pc = change_pc(g_pc + IND_SIZE);
	return (ret);
}

static int		third_arg(int cmd, t_data *data)
{
	int			ret;

	ret = 1;
	if (data->asml[cmd].arg_num < 3 && ((g_acb >> 2) & 3) == 0)
		return (1);
	if (((g_acb >> 2) & 3) == REG_CODE && data->asml[cmd].arg_type & 4)
		g_args[2] = read_int(data, g_pc, REG_SIZE);
	else if (((g_acb >> 2) & 3) == DIR_CODE && data->asml[cmd].arg_type & 2)
		g_args[2] = read_int(data, g_pc, data->asml[cmd].label_size);
	else if (((g_acb >> 2) & 3) == IND_CODE && data->asml[cmd].arg_type & 1)
		g_args[2] = read_int(data, g_pc, IND_SIZE);
	else
		ret = 0;
	if (((g_acb >> 2) & 3) == REG_CODE)
		g_pc = change_pc(g_pc + REG_SIZE);
	else if (((g_acb >> 2) & 3) == DIR_CODE)
		g_pc = change_pc(g_pc + data->asml[cmd].label_size);
	else if (((g_acb >> 2) & 3) == IND_CODE)
		g_pc = change_pc(g_pc + IND_SIZE);
	return (ret);
}

void			handling_args(int cmd, t_proc **tmp, t_data *data)
{
	int			valid_acb;

	valid_acb = 0;
	g_acb = 0;
	g_pc = change_pc((*tmp)->pc + 1);
	while (g_acb < 4)
		g_args[g_acb++] = 0;
	g_acb = (data->asml[cmd].cod_oct) ? read_int(data, g_pc, 1) : 0;
	if (data->asml[cmd].cod_oct == 0)
		g_args[0] = read_int(data, g_pc, data->asml[cmd].label_size);
	else
	{
		g_pc = change_pc(g_pc + 1);
		valid_acb += first_arg(cmd, data);
		valid_acb += (data->asml[cmd].arg_num > 1) ? second_arg(cmd, data) : 1;
		valid_acb += (data->asml[cmd].arg_num > 2) ? third_arg(cmd, data) : 1;
		g_args[3] = g_acb;
	}
	if (data->asml[cmd].cod_oct == 0 || valid_acb == 3)
		exec_command(cmd, g_args, *tmp, data);
	shift_pc_on_map(data, *tmp, g_pc, cmd);
}
