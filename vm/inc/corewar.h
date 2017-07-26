/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 19:27:53 by ochayche          #+#    #+#             */
/*   Updated: 2017/06/05 19:27:54 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**		allowed function:
**		open
**		read
**		lseek
**		write
**		close
**		malloc
**		realloc
**		free
**		perror
**		strerror
**		exit
*/

#ifndef COREWAR_H
# define COREWAR_H
# include <../../inc/libft/inc/libft.h>
# include <../../inc/ft_printf/ft_printf.h>
# include <../../inc/op.h>
# include <fcntl.h>
# include <ncurses.h>

# define USAGE1 "usage: ./corewar [-v] [-dump nbr_cycles] [[-n number] champion"
# define USAGE2 "1.cor] ...\n"
# define ERROR_SIZE11 "Error: File %s has a code size that differs from what it"
# define ERROR_SIZE12 "s header says\n"
# define ERROR_SIZE21 "The champion's size exceeds the one declared in the head"
# define ERROR_SIZE22 "er\n"
# define USAGE USAGE1 USAGE2
# define ERROR_SIZE1 ERROR_SIZE11 ERROR_SIZE12
# define ERROR_SIZE2 ERROR_SIZE21 ERROR_SIZE22

int						g_yline;

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;
typedef long long		t_lint;

typedef struct			s_asml
{
	char				name[6];
	short				arg_type;
	short				arg_num;
	int					cycles;
	short				label_size;
	short				carry;
	short				cod_oct;
}						t_asml;

typedef struct			s_proc
{
	t_uint				id;
	int					cmd;
	int					player_id;
	int					pc;
	t_uint				last_live;
	int					cycles_to_exec;
	int					reg[REG_NUMBER];
	int					carry;
	struct s_proc		*next;
}						t_proc;

typedef struct			s_player
{
	int					player_id;
	char				alive;
	char				*name;
	int					prog_size;
	char				*comment;
	t_uint				last_live;
	t_uint				lives_in_curr;
	t_uchar				*byte_code;
	struct s_player		*next;
}						t_player;

typedef struct			s_data
{
	t_lint				dump_arg;
	t_uchar				*map;
	t_uchar				*color;
	t_uint				cycle;
	int					cycle_to_die;
	t_uint				checks;
	t_uint				last_check;
	t_uint				lives_in_curr;
	t_uint				num_of_proc;
	t_uint				num_of_players;
	t_asml				asml[16];
	t_player			*players;
	t_proc				*processes;
	int					visual_flag;
	int					winner_id;
}						t_data;

int						read_int(t_data *data, int pc, size_t size);
void					game_on(t_data *data);
void					asml_default(t_asml asml[16]);
void					delete_proc_by_id(t_uint proc_id, t_proc **root);
void					delete_proc(t_proc **root);
t_proc					*create_proc(t_proc **root);
t_uint					change_pc(t_uint pc);
void					inheritance(t_uint dest_id, t_uint src_id, t_data *data,
																	int shift);
void					init_data(t_data *data);
void					map_init(t_data *data);
void					proc_init_basic(t_data *data);

/*
** read args and players
*/

void					ft_usage(t_data *data);
void					read_args(t_data *data, char **av, int ar);
void					read_player(t_data *data, char *av, int n);
t_uint					big_to_little_endian(t_uint n);
int						read_size(int fd);
int						check_magic(int fd);
char					*read_byte_code(int fd, int prog_size, char *str);
char					*read_comment(int fd);
char					*read_name(int fd);
void					sort_players(t_data *data);
void					sort_list(t_data *data);
void					dump(t_data *data);

/*
** free stuff
*/

void					destruct(t_data *data);
void					delete_every_proc(t_proc **root);
void					free_all_players(t_player **root);
void					free_one_player_node(t_player *node);
void					destruct_fail_malloc(t_data *data);

/*
** functions
*/

void					live(int args[4], t_proc *proc, t_data *data);
void					add(int args[4], t_proc *proc, t_data *data);
void					sub(int args[4], t_proc *proc, t_data *data);
void					zjmp(int args[4], t_proc *proc, t_data *data);
void					lfork(int args[4], t_proc *proc, t_data *data);
void					ft_fork(int args[4], t_proc *proc, t_data *data);
void					sti(int args[4], t_proc *proc, t_data *data);
void					st(int args[4], t_proc *proc, t_data *data);
void					lldi(int args[4], t_proc *proc, t_data *data);
void					ldi(int args[4], t_proc *proc, t_data *data);
void					lld(int args[4], t_proc *proc, t_data *data);
void					ld(int args[4], t_proc *proc, t_data *data);
void					ft_or(int args[4], t_proc *proc, t_data *data);
void					ft_xor(int args[4], t_proc *proc, t_data *data);
void					ft_and(int args[4], t_proc *proc, t_data *data);
void					ft_aff(int args[4], t_proc *proc, t_data *data);
int						read_4_bytes(t_uchar *map, int index);
void					write_4_bytes(t_data *data, t_proc *proc, int index,
																	int var);
int						is_valid_reg(int reg);
int						get_arg(char bin_code, t_proc *proc, int arg,
																t_uchar *map);
int						get_arg_noidx(char bin_code, t_proc *proc, int arg,
																t_uchar *map);
void					handling_args(int cmd, t_proc **tmp, t_data *data);
void					shift_pc_on_map(t_data *data, t_proc *proc, int g_pc,
																	int cmd);
void					exec_command(int cmd, int args[4], t_proc *proc,
																t_data *data);
void					ressurection(t_player **player);
t_uint					generate_id(t_proc *list);
void					redraw_pc(t_data *data);
void					reduce_cycle_to_die(t_data *data);

/*
** visualization
*/

/*
** s_viz
** used only in visualization
** used only stack memmory
*/

typedef struct			s_viz
{
	int					pause;
	double				hz;
	int					y;
	int					x;
	t_uint				abs_lives;
	t_uint				abs_proportion[MAX_PLAYERS];
	t_uint				rel_proportion[MAX_PLAYERS];
	int					print_last;
}						t_viz;

void					visual_main(t_data *data, t_viz *viz);
void					init_window(t_data *data, t_viz *viz);
void					show_map(t_data *data, t_viz *viz);
void					destroy_window(t_data *data, t_viz *viz);
void					print_border_box(void);
void					print_static_info(t_data *data, t_viz *viz);
void					print_dynamic_info(t_data *data, t_viz *viz);
void					key_event(t_data *data, t_viz *viz);
void					pause_event(t_data *data, t_viz *viz);
void					find_proportion(t_data *data, t_viz *viz, int *y);

#endif
