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

//Eto nado ubrat!!!
#include <stdio.h>
#define ft_printf	printf

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

// 1 - REG
// 2 - DIR
// 3 - IND
//     RDI 000 R00

typedef struct		s_asml
{
	char	name[6];
	short	arg_type;
	short	arg_num;
	int		cycles;
	short	label_size;
	short	carry;
	short	cod_oct;
}					t_asml;

typedef struct		s_body
{
	size_t			size;
	short			cmd;
	short			type;
	char			*label;
	char			*link_1;
	char			*link_2;
	char			*link_3;
	long long		arg1;
	long long		arg2;
	long long		arg3;
	struct s_body	*next;
}					t_body;

int					search_label(char *line, char **label, size_t *i);
int					search_cmd(char *line, short *cmd, size_t *i, t_asml asml[16]);
int					search_args(char *line, t_body **node, size_t *i, t_asml asml[16]);

void				read_error(char **line, t_body **root);
int					inv_arg(char *name, short arg_num, char ***mas);
void				empty_code(void);
void				syntax_error(unsigned int line_num, unsigned int column, char **line);
void				syntax_body_error(unsigned int line_num, unsigned int column,
					char **line, t_body **root);
					
void				asml_default(t_asml asml[16]);
t_header			make_header(int fd);
t_body				*make_body(int fd, unsigned int line_num, t_asml asml[16]);
int					body_create(t_body **root);
void				body_delete(t_body **root);

int					empty(char *line);
int					ft_isspace(int c);
int					free_char_mas(char ***mas);
int					count_sym(const char *line, char c);

#endif
