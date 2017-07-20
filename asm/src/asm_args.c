/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:39:53 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:39:58 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** Registry - 01 (01 00 00 00 - 64)
** Direct   - 11 (11 00 00 00 - 192)
** Indirect - 10 (10 00 00 00 - 128)
*/

int				accept_registry(char *line, char **link, int *arg, size_t *i)
{
	size_t j;

	*i += 1;
	j = *i;
	while (line[j] && ft_isspace(line[j]) == 0)
		if (ft_isdigit(line[j++]) == 0)
		{
			*i = j - 1;
			return (0);
		}
	*arg = ft_atoi(line + *i);
	if (*arg < 1 || *arg > 99)
	{
		ft_putstr_fd("Invalid register number. ", 2);
		return (0);
	}
	*i = j;
	*link = ft_strdup("registry");
	if (!(*link))
		return (-1);
	return (REG_CODE);
}

static int		handling_label(char *line, char **link, size_t *i)
{
	size_t j;
	size_t size;

	*i += 1;
	j = *i;
	if (line[j] == '\0' || ft_isspace(line[j]) != 0)
	{
		ft_putstr_fd("Invalid characters in label. ", 2);
		return (0);
	}
	while (line[j] && ft_isspace(line[j]) == 0)
		if (!ft_strchr(LABEL_CHARS, line[j]))
		{
			*i = j;
			ft_putstr_fd("Invalid characters in label. ", 2);
			return (0);
		}
		else
			j++;
	size = j - *i;
	if (!(*link = ft_strnew(size)))
		return (-1);
	*link = ft_strncpy(*link, line + *i, size);
	*i = j;
	return (1);
}

int				accept_direct(char *line, char **link, int *arg, size_t *i)
{
	int		res;
	size_t	j;

	*i += 1;
	if (line[*i] == LABEL_CHAR)
	{
		if ((res = handling_label(line, link, i)) != 1)
			return (res);
		return (DIR_CODE);
	}
	j = *i;
	if (line[j] == '-' && line[j + 1] && line[j + 1] != '0')
		j++;
	while (line[j] && ft_isspace(line[j]) == 0)
		if (ft_isdigit(line[j++]) == 0)
		{
			*i = j - 1;
			return (0);
		}
	*arg = ft_atoi(line + *i);
	*i = j;
	return (DIR_CODE);
}

int				accept_indirect(char *line, char **link, int *arg, size_t *i)
{
	int		res;
	size_t	j;

	if (line[*i] == LABEL_CHAR)
	{
		if ((res = handling_label(line, link, i)) != 1)
			return (res);
		return (IND_CODE);
	}
	j = *i;
	if ((line[j] == '-' || line[j] == '+') && line[j + 1] && line[j + 1] != '0')
		j++;
	while (line[j] && ft_isspace(line[j]) == 0)
		if (ft_isdigit(line[j++]) == 0)
		{
			*i = j - 1;
			return (0);
		}
	*arg = ft_atoi(line + *i);
	*i = j;
	return (IND_CODE);
}

int				end_of_arg(char *line, size_t i, int j, short arg_num)
{
	if (j == 8)
		j = 2;
	else if (j == 64)
		j = 3;
	while (line[i])
	{
		if (j == arg_num && (line[i] == COMMENT_CHAR ||
			line[i] == SECOND_COMMENT_CHAR))
			break ;
		if (ft_isspace(line[i]) == 0)
			return (i);
		i++;
	}
	return (-2);
}
