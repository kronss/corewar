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

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include "op.h"
# include <errno.h>
# include <fcntl.h>

# define live	1
# define ld		2
# define st		3
# define add	4
# define sub	5
# define and	6
# define or		7
# define xor	8
# define zjmp	9
# define ldi	10
# define sti	11
# define fork	12
# define lld	13
# define lldi	14
# define lfork	15
# define aff	16

# define USAGE " [-a] <sourcefile.s>\n    -a : Instead of creating\
 a .cor file, outputs a stripped and annotated\
 version of the code to the standard output\n"

typedef struct		s_body
{
	size_t			size;
	short int		cmd;
	short int		type;
	char			*label;
	char			*link_1;
	char			*link_2;
	char			*link_3;
	long long		arg1;
	long long		arg2;
	long long		arg3;
	struct s_body	*next;
}					t_body;

int		search_label(char *line, char **label, size_t *i);
int		search_cmd(char *line, short int *cmd, size_t *i);
int		search_args(char *line, t_body **node, size_t *i);

void				empty_code(void);
int					body_create(t_body **root);
void				body_delete(t_body **root);


void				read_error(char **line, t_body **root);
void				syntax_error(unsigned int line_num, unsigned int column, char **line);
void				syntax_body_error(unsigned int line_num, unsigned int column,
					char **line, t_body **root);
t_header			make_header(int fd);
t_body				*make_body(int fd, unsigned int line_num);
int					ft_isspace(int c);

#endif