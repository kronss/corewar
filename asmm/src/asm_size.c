/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:43:39 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:43:42 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	count_size(t_body *list)
{
	unsigned int	size;

	size = 0;
	while (list)
	{
		if (list->cmd != -1)
			size += list->size[0];
		list = list->next;
	}
	return (size);
}

static int			count_distance_to_label(unsigned int start,
	unsigned int end, t_body *tmp)
{
	unsigned int	count;
	int				distance;

	count = 0;
	distance = 0;
	while (tmp && count < end)
	{
		if (count >= start && tmp->cmd != -1)
			distance += tmp->size[0];
		tmp = tmp->next;
		count++;
	}
	return (distance);
}

static int			search_label_in_list(char **label,
	t_body **root, unsigned int cmd_line)
{
	t_body			*tmp;
	unsigned int	label_line;

	label_line = 0;
	tmp = *root;
	while (tmp)
	{
		if (tmp->label && ft_strcmp(*label, tmp->label) == 0)
			break ;
		tmp = tmp->next;
		label_line++;
	}
	if (!tmp)
	{
		ft_putstr_fd("The label \"", 2);
		ft_putstr_fd(*label, 2);
		ft_putstr_fd("\" does not exist.\n", 2);
		body_delete(root);
		exit(-7);
	}
	ft_strdel(label);
	if (label_line >= cmd_line)
		return (count_distance_to_label(cmd_line, label_line, *root));
	return (-1 * count_distance_to_label(label_line, cmd_line, *root));
}

static void			label_to_number(t_body **root)
{
	t_body			*tmp;
	unsigned int	count;

	count = 0;
	tmp = *root;
	while (tmp)
	{
		if (tmp->cmd != -1)
		{
			if (tmp->link_1 && tmp->arg1 == 0)
				tmp->arg1 = search_label_in_list(&(tmp->link_1), root, count);
			if (tmp->link_2 && tmp->arg2 == 0)
				tmp->arg2 = search_label_in_list(&(tmp->link_2), root, count);
			if (tmp->link_3 && tmp->arg3 == 0)
				tmp->arg3 = search_label_in_list(&(tmp->link_3), root, count);
		}
		tmp = tmp->next;
		count++;
	}
}

unsigned int		resize(t_body **root, t_asml asml[16])
{
	t_body		*tm;
	short		k;

	tm = *root;
	while (tm)
	{
		if (tm->cmd != -1)
		{
			tm->size[0] = 1;
			if (asml[tm->cmd].cod_oct == 1)
				tm->size[0] += 1;
			k = 4;
			while (--k > 0)
				if (((tm->type >> (2 * k)) & 3) == REG_CODE)
					tm->size[4 - k] = REG_SIZE;
				else if (((tm->type >> (2 * k)) & 3) == IND_CODE)
					tm->size[4 - k] = IND_SIZE;
				else if (((tm->type >> (2 * k)) & 3) == DIR_CODE)
					tm->size[4 - k] = asml[tm->cmd].label_size;
			tm->size[0] = tm->size[0] + tm->size[1] + tm->size[2] + tm->size[3];
		}
		tm = tm->next;
	}
	label_to_number(root);
	return (count_size(*root));
}
