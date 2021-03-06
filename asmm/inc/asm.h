/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrush <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:27:56 by atrush            #+#    #+#             */
/*   Updated: 2017/07/20 15:28:08 by atrush           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../inc/ft_printf/ft_printf.h"
# include "../../inc/libft/inc/libft.h"
# include "../../inc/op.h"
# include <errno.h>
# include <fcntl.h>

# define SECOND_COMMENT_CHAR	';'
# define RED					"\033[31m"
# define GREEN					"\033[32m"
# define YELLOW					"\033[33m"
# define DEFAULT				"\033[0m"
# define US1					" [-d <sourcefile.cor>] <sourcefile.s>\n"
# define US2					"    -d <sourcefile.cor> : Disassambles any "
# define US3					".cor file back into its respective .s file\n"

typedef struct		s_asml
{
	char			name[6];
	short			arg_type;
	short			arg_num;
	int				cycles;
	short			label_size;
	short			carry;
	short			cod_oct;
}					t_asml;

typedef struct		s_body
{
	short			size[4];
	short			cmd;
	short			type;
	char			*label;
	char			*link_1;
	char			*link_2;
	char			*link_3;
	int				arg1;
	int				arg2;
	int				arg3;
	struct s_body	*next;
}					t_body;

int					open_read_file(const char *filename);
int					disasm(t_asml asml[16], int argc, char **argv);
int					with_opcode(int cor_fd, int s_fd, int cmd, t_asml asml[16]);
void				write_to_file(int fd, t_header head,
					t_body **root, t_asml asml[16]);

int					read_int(int fd, int *value, size_t size);
int					read_header(int cor_fd, int s_fd);

int					search_label(char *line, char **label, size_t *i);
int					search_cmd(char *line, short *cmd,
					size_t *i, t_asml asml[16]);
int					search_args(char *line, t_body **node,
					size_t *i, t_asml asml[16]);

int					accept_registry(char *line, char **link,
					int *arg, size_t *i);
int					accept_indirect(char *line, char **link,
					int *arg, size_t *i);
int					accept_direct(char *line, char **link, int *arg, size_t *i);
int					end_of_arg(char *line, size_t i, int j, short arg_num);

void				read_error(char **line, t_body **root);
int					inv_arg(char *name, short arg_num, char ***mas);
void				empty_code(void);
void				syntax_error(unsigned int line_num,
					unsigned int column, char **line);
void				syntax_body_error(unsigned int line_num,
					unsigned int column, char **line, t_body **root);

void				asml_default(t_asml asml[16]);
t_header			make_header(int fd);
t_body				*make_body(int fd, unsigned int line_num, t_asml asml[16]);
int					body_create(t_body **root);
int					body_delete(t_body **root);

int					empty(char *line);
unsigned int		resize(t_body **root, t_asml asml[16]);

int					ft_isspace(int c);
int					incorrect_arg(size_t value);
int					free_char_mas(char ***mas);
int					count_sym(const char *line, char c);

#endif
