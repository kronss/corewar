/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_additionally.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 16:02:32 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 14:32:52 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		incorrect_arg(size_t value)
{
	ft_putstr_fd("Incorrect arguments. ", 2);
	return ((int)value);
}

int		count_sym(const char *line, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (line && line[i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == SECOND_COMMENT_CHAR)
			break ;
		if (line[i] == c)
			count++;
		i++;
	}
	return (count);
}

int		free_char_mas(char ***mas)
{
	size_t	i;

	i = 0;
	if (!mas || !(*mas))
		return (0);
	while ((*mas)[i])
	{
		free((*mas)[i]);
		(*mas)[i] = NULL;
		i++;
	}
	free(*mas);
	*mas = NULL;
	return (0);
}

int		ft_isspace(int c)
{
	if (c == (int)' ' || c == (int)'\f' || c == (int)'\n' || c == (int)'\r' ||
			c == (int)'\t' || c == (int)'\v' || c == (int)'\0')
		return (1);
	return (0);
}
