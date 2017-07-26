/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:02:39 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/07/04 18:02:47 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		delete_every_proc(t_proc **root)
{
	t_proc	*tmp;

	while (*root)
	{
		tmp = *root;
		*root = tmp->next;
		free(tmp);
	}
	*root = NULL;
}

void		delete_proc_by_id(t_uint proc_id, t_proc **root)
{
	t_proc	*tmp;
	t_proc	*prev;

	tmp = *root;
	prev = NULL;
	while (tmp)
	{
		if (tmp->id == proc_id)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*root = tmp->next;
			free(tmp);
			tmp = NULL;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

t_uint		generate_id(t_proc *list)
{
	t_uint	id;

	id = 0;
	while (list)
	{
		if (list->id > id)
			id = list->id;
		list = list->next;
	}
	return (id + 1);
}

t_proc		*create_proc(t_proc **root)
{
	t_proc	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if (!(tmp = (t_proc*)malloc(sizeof(t_proc))))
		return (NULL);
	tmp->next = *root;
	tmp->id = generate_id(*root);
	tmp->cmd = -2;
	tmp->player_id = 0;
	tmp->pc = 0;
	tmp->last_live = 0;
	tmp->cycles_to_exec = -1;
	while (++i < REG_NUMBER)
		tmp->reg[i] = 0;
	tmp->carry = 0;
	*root = tmp;
	return (tmp);
}

void		inheritance(t_uint dest_id, t_uint src_id, t_data *data, int shift)
{
	t_proc	*src;
	t_proc	*dest;

	dest = data->processes;
	src = data->processes;
	while (dest && dest->id != dest_id)
		dest = dest->next;
	while (src && src->id != src_id)
		src = src->next;
	dest->player_id = src->player_id;
	dest->pc = change_pc(src->pc + shift);
	dest->cycles_to_exec = -1;
	dest->carry = src->carry;
	dest->last_live = src->last_live;
	dest_id = 0;
	while (dest_id < REG_NUMBER)
	{
		dest->reg[dest_id] = src->reg[dest_id];
		dest_id++;
	}
	data->num_of_proc += 1;
}
