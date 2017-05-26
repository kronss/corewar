/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:07:23 by atrush            #+#    #+#             */
/*   Updated: 2017/05/25 15:07:29 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "op.h"
#include <errno.h>
#include <fcntl.h>

# define USAGE " [-a] <sourcefile.s>\n    -a : Instead of creating\
 a .cor file, outputs a stripped and annotated\
 version of the code to the standard output\n"

t_header	make_header(int fd);
int			ft_isspace(int c);

typedef struct		s_body
{
	unsigned int	ma;
}					t_body;

#endif
