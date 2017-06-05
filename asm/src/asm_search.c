/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 14:07:25 by atrush            #+#    #+#             */
/*   Updated: 2017/06/02 14:07:27 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				search_label(char *line, char **label, size_t *i)
{
	size_t j;
	size_t size;

	j = 0;
	while (line[j] && ft_isspace(line[j]) != 0)
		j++;
	*i = j;
	while (line[j] && ft_isspace(line[j]) == 0 && line[j] != COMMENT_CHAR)
		j++;
	if (line[--j] != LABEL_CHAR)
		return (1);
	size = j - *i;

	while (*i < j)
		if (!ft_strchr(LABEL_CHARS, line[*i]))
			return (0);
		else
			*i += 1;
	*i += 1;
	if (!(*label = ft_strnew(size)))
		return (-1);
	*label = ft_strncpy(*label, line + j - size, size);
	return (1);
}

int				search_cmd(char *line, short *cmd, size_t *i, t_asml asml[16])
{
	short k;
	
	while (line[*i] && ft_isspace(line[*i]) != 0)
		*i += 1;
	k = 16;
	while (--k > -1)
		if (!ft_strncmp(line + *i, asml[k].name, ft_strlen(asml[k].name)))
			break;
	*cmd = k;
	if (*cmd == -1)
		return (0);
	*i += ft_strlen(asml[*cmd].name);
	if (!line[*i] || ft_isspace(line[*i]) == 0)
		return (0);
	*i += 1;
	if (empty(line + *i) == -1)
		return (0);
	return (1);
}

static int		incorrect_arg(size_t value)
{
	ft_putstr_fd("Incorrect arguments! ", 2);
	return ((int)value);
}


/*
** j - number of argument
*/

static int		analysis_arg(const char *line, t_body **node,
				t_asml asml[16], int j)
{
	size_t i;
	
	i = 0;
	if (j == 2)
		j = 8;
	else if (j == 3)
		j = 64;
	while (line[i] && ft_isspace(line[i]) != 0)
		i++;
	if (line[i] == 'r')
	{
		if (asml[(*node)->cmd].arg_type & (256 / j))
			if 
		
	}
	else if ()
	return (incorrect_arg(i));
}

int				search_args(char *line, t_body **node, size_t *i, t_asml asml[16])
{
	char	**mas;
	int		j;
	int		res;
	
	mas = ft_strsplit(line + *i, SEPARATOR_CHAR);
	j = 0;
	while (mas && mas[j])
		j++;
	if (j != asml[(*node)->cmd].arg_num ||
		count_sym(line + *i, SEPARATOR_CHAR) + 1 != asml[(*node)->cmd].arg_num)
		return (inv_arg(asml[(*node)->cmd].name, asml[(*node)->cmd].arg_num, &mas));
	j = -1;
	while (++j < asml[(*node)->cmd].arg_num)
	{
		if ((res = analysis_arg(mas[j], node, asml, j + 1)) == -1)
			return (free_char_mas(&mas) - 1);
		if (res >= 0)
			*i += res;
		if (res >= 0)
			return (free_char_mas(&mas));
		*i += ft_strlen(mas[j]) + 1;
	}
	*i = *i - free_char_mas(&mas) - 1;
	return (1);
}

