/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_body_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 14:46:21 by atrush            #+#    #+#             */
/*   Updated: 2017/05/31 14:46:24 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			body_delete(t_body **root)
{
	t_body *tmp;

	while (*root)
	{
		tmp = *root;
		*root = tmp->next;
		if (tmp->label)
			ft_strdel(&(tmp->label));
		if (tmp->link_1)
			ft_strdel(&(tmp->link_1));
		if (tmp->link_2)
			ft_strdel(&(tmp->link_2));
		if (tmp->link_3)
			ft_strdel(&(tmp->link_3));
		free(tmp);
	}
}

static void		default_values(t_body **node)
{
	(*node)->next = NULL;
	(*node)->size = 0;
	(*node)->cmd = -1;
	(*node)->type = 0;
	(*node)->label = NULL;
	(*node)->link_1 = NULL;
	(*node)->link_2 = NULL;
	(*node)->link_3 = NULL;
	(*node)->arg1 = 0;
	(*node)->arg2 = 0;
	(*node)->arg3 = 0;
}

int				body_create(t_body **root)
{
	t_body *tmp;

	tmp = *root;
	if (!tmp)
	{
		if (!(tmp = (t_body*)malloc(sizeof(t_body))))
			return (0);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_body*)malloc(sizeof(t_body))))
			return (0);
		tmp = tmp->next;
	}
	default_values(&tmp);
	if (!(*root))
		*root = tmp;
	return (1);
}
