#include "corewar.h"

int			g_opcode;

static int  registry(int cor_fd, int s_fd)
{
	int value;
	
	if (!read_int(cor_fd, &value, REG_SIZE))
		return (0);
	if (value < 1 || value > 99)
		return (0);
	ft_putstr_fd(" r", s_fd);
	ft_putnbr_fd(value, s_fd);
	return (REG_SIZE);
}

static int  direct(int cor_fd, int s_fd, size_t size)
{
	int value;
	
	if (!read_int(cor_fd, &value, size))
		return (0);
	ft_putstr_fd(" ", s_fd);
	ft_putchar_fd(DIRECT_CHAR, s_fd);
	ft_putnbr_fd(value, s_fd);
	return (size);
}

static int  indirect(int cor_fd, int s_fd)
{
	int value;
	
	if (!read_int(cor_fd, &value, IND_SIZE))
		return (0);
	ft_putstr_fd(" ", s_fd);
	ft_putnbr_fd(value, s_fd);
	return (IND_SIZE);
}

static int	more_than_one(int cor_fd, int s_fd, int cmd, t_asml asml[16])
{
	int res;
	
	res = 0;
	if (((g_opcode >> 4) & 3) == REG_CODE && (asml[cmd].arg_type & 32))
		res = registry(cor_fd, s_fd);
	else if (((g_opcode >> 4) & 3) == DIR_CODE && (asml[cmd].arg_type & 16))
		res = direct(cor_fd, s_fd, asml[cmd].label_size);
	else if (((g_opcode >> 4) & 3) == IND_CODE && (asml[cmd].arg_type & 8))
		res = indirect(cor_fd, s_fd);
	if (res == 0 || (asml[cmd].arg_num == 2 &&
		(((g_opcode >> 2) & 3) || (g_opcode & 3))))
		return (0);
	if (asml[cmd].arg_num == 2)
		return (res);
	ft_putchar_fd(SEPARATOR_CHAR, s_fd);
	if (((g_opcode >> 2) & 3) == REG_CODE && (asml[cmd].arg_type & 4))
		cmd = registry(cor_fd, s_fd);
	else if (((g_opcode >> 2) & 3) == DIR_CODE && (asml[cmd].arg_type & 2))
		cmd = direct(cor_fd, s_fd, asml[cmd].label_size);
	else if (((g_opcode >> 2) & 3) == IND_CODE && (asml[cmd].arg_type & 1))
		cmd = indirect(cor_fd, s_fd);
	else
		cmd = 0;
	if (cmd == 0 || (g_opcode & 3))
		return (0);
	return (res + cmd);
}

int     	with_opcode(int cor_fd, int s_fd, int cmd, t_asml asml[16])
{
	int res;
	
	if (!read_int(cor_fd, &g_opcode, 1))
		return (0);
	res = 0;
	if (((g_opcode >> 6) & 3) == REG_CODE && (asml[cmd].arg_type & 256))
		res = registry(cor_fd, s_fd);
	else if (((g_opcode >> 6) & 3) == DIR_CODE && (asml[cmd].arg_type & 128))
		res = direct(cor_fd, s_fd, asml[cmd].label_size);
	else if (((g_opcode >> 6) & 3) == IND_CODE && (asml[cmd].arg_type & 64))
		res = indirect(cor_fd, s_fd);
	if (res == 0 || (asml[cmd].arg_num == 1 &&
		(((g_opcode >> 4) & 3) || ((g_opcode >> 2) & 3) || (g_opcode & 3))))
		return (0);
	if (asml[cmd].arg_num == 1)
		return (res);
	ft_putchar_fd(SEPARATOR_CHAR, s_fd);
	if ((cmd = more_than_one(cor_fd, s_fd, cmd, asml)) == 0)
		return (0);
	return (res + cmd);
}
