/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdoroshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 19:39:58 by vdoroshy          #+#    #+#             */
/*   Updated: 2017/06/30 19:40:09 by vdoroshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		read_dump_arg(t_data *data, char *av)
{
	if (av && data->dump_arg == -2)
	{
		if ((data->dump_arg = ft_atoi_ptv(av)) == -1)
		{
			ft_usage(data);
		}
	}
	else
	{
		ft_usage(data);
	}
}

/*
**	read_flags() -- read flags from all $valid_position in STDIN
**	read $flags_arguments followed by $valid_position
*/

static void		read_flags(t_data *data, char **av, int *i)
{
	if (!ft_strcmp("-dump", av[*i]))
	{
		++(*i);
		read_dump_arg(data, av[*i]);
	}
	else if (!ft_strcmp("-n", av[*i]))
	{
		++(*i);
		if (av[*i])
		{
			++(*i);
			read_player(data, av[*i], ft_atoi(av[(*i) - 1]));
		}
		else
			ft_usage(data);
	}
	else if (!ft_strcmp("-v", av[*i]))
	{
		if (data->visual_flag == 0)
			data->visual_flag = 1;
		else
			ft_usage(data);
	}
	else
		ft_usage(data);
}

static void		check_identical_pos2(char **av, int ar, int i, t_data *data)
{
	char		num;

	num = av[i][0];
	i = i + 2;
	while (i < ar)
	{
		if (!ft_strcmp("-n", av[i]))
		{
			++i;
			if (i >= ar || i + 1 >= ar || !av[i] ||
				('1' > av[i][0] && av[i][0] > '4') ||
				av[i][1] != '\0' || av[i][0] == num)
			{
				ft_usage(data);
			}
		}
		++i;
	}
}

static void		check_identical_pos1(char **av, int ar, t_data *data)
{
	int			i;

	i = 1;
	while (i < ar)
	{
		if (!ft_strcmp("-n", av[i]))
		{
			++i;
			if ((i < ar && i + 1 < ar) && av[i] &&
				('1' <= av[i][0] && av[i][0] <= '4') && (av[i][1] == '\0'))
			{
				check_identical_pos2(av, ar, i, data);
			}
			else
			{
				ft_usage(data);
			}
		}
		++i;
	}
}

void			read_args(t_data *data, char **av, int ar)
{
	int			i;

	check_identical_pos1(av, ar, data);
	i = 1;
	while (i < ar)
	{
		if (av[i][0] == '-')
		{
			read_flags(data, av, &i);
		}
		else
		{
			read_player(data, av[i], 0);
		}
		++i;
	}
	sort_players(data);
}
