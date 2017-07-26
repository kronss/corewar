/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 20:31:11 by ochayche          #+#    #+#             */
/*   Updated: 2017/06/14 20:31:12 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_player	*malloc_player_node(int n)
{
	t_player	*tmp;

	tmp = (t_player *)malloc(sizeof(t_player));
	if (tmp == NULL)
	{
		return (NULL);
	}
	tmp->player_id = n - 1;
	tmp->alive = 0;
	tmp->name = NULL;
	tmp->prog_size = 0;
	tmp->comment = NULL;
	tmp->last_live = 0;
	tmp->lives_in_curr = 0;
	tmp->byte_code = NULL;
	tmp->next = NULL;
	return (tmp);
}

static void		add_node_to_players(t_player *node, t_data *data)
{
	t_player	*curr;

	curr = data->players;
	if (curr == NULL)
	{
		data->players = node;
		return ;
	}
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = node;
}

static void		open_error(t_data *data, char *str)
{
	ft_printf("Can't read source file %s\n", str);
	destruct(data);
	exit(1);
}

void			read_player(t_data *data, char *str, int n)
{
	int			fd;
	t_player	*node;

	if ((fd = open(str, O_RDONLY)) == -1)
		open_error(data, str);
	node = malloc_player_node(n);
	if (node == NULL)
	{
		destruct(data);
		exit(666);
	}
	if (!check_magic(fd) || !(node->name = read_name(fd))
	|| ((node->prog_size = read_size(fd)) == -1)
	|| !(node->comment = read_comment(fd))
	|| !(node->byte_code = (t_uchar *)read_byte_code(fd, node->prog_size, str)))
	{
		ft_printf("ERROR: invalid player\n");
		free_one_player_node(node);
		destruct(data);
		exit(1);
	}
	add_node_to_players(node, data);
	data->num_of_players += 1;
	close(fd);
}
