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

static int		cmdcmp(char *line)
{
	if (!ft_strncmp(line, "live", 4))
		return (1);
	if (!ft_strncmp(line, "add", 4))
		return (1);
	if (!ft_strncmp(line, "sub", 4))
		return (1);
	if (!ft_strncmp(line, "and", 4))
		return (1);
	if (!ft_strncmp(line, "xor", 4))
		return (1);
	if (!ft_strncmp(line, "or", 4))
		return (1);
	if (!ft_strncmp(line, "zjmp", 4))
		return (1);
	if (!ft_strncmp(line, "ldi", 4))
		return (1);
	if (!ft_strncmp(line, "sti", 4))
		return (1);
	if (!ft_strncmp(line, "ld", 4))
		return (1);
	if (!ft_strncmp(line, "st", 4))
		return (1);
	return (0);
}

int				search_cmd(char *line, short int *cmd, size_t *i)
{
	size_t j;

	while (line[*i] && ft_isspace(line[*i]) != 0)
		*i += 1;
	(void)cmd;
	(void)j;
	cmdcmp(line);
	
	return (1);
}

int				search_args(char *line, t_body **node, size_t *i)
{
	(void)line;
	(void)node;
	(void)i;
	return (0);
}

