#include "corewar.h"

static int	write_hex(int fd, int value, size_t size)
{
	unsigned char   *str;
	size_t          i;
	
	i = 0;
	str = NULL;
	if (!(str = (unsigned char *)malloc(sizeof(unsigned char) * (size + 1))))
		return (0);
	while (i < size)
		str[i++] = 0;
	if (value < 0)
	{
		str[0] += 128;
		if (size == 4)
			value += 2147483648;
		else if (size == 2)
			value += 32768;
	}
	while (value != 0)
	{
		str[--size] += ABS(value % 16) + 16 * ABS((value / 16) % 16);
		value = value / 256;
	}
	write(fd, str, i);
	free(str);
	return (1);
}

static void		malloc_error(int fd, t_body **root)
{
	body_delete(root);
	close(fd);
	perror("");
	exit (-8);
}

static int		write_header(int fd, t_header head)
{
	if (!(write_hex(fd, head.magic, 4)))
		return (0);
	write(fd, head.prog_name, PROG_NAME_LENGTH);
	if (!(write_hex(fd, 0, 4)))
		return (0);
	if (!(write_hex(fd, head.prog_size, 4)))
		return (0);
	write(fd, head.comment, COMMENT_LENGTH);
	if (!(write_hex(fd, 0, 4)))
		return (0);
	return (1);
}

void			write_to_file(int fd, t_header head, t_body **root, t_asml asml[16])
{
	t_body	*tmp;
	
	if (!(write_header(fd, head)))
		malloc_error(fd, root);
	tmp = *root;
	while (tmp)
	{
		if (tmp->cmd != -1)
		{
			if (!(write_hex(fd, tmp->cmd + 1, 1)))
				malloc_error(fd, root);
			if (asml[tmp->cmd].cod_oct == 1 && !(write_hex(fd, tmp->type, 1)))
				malloc_error(fd, root);
			if (asml[tmp->cmd].arg_num > 0 && !(write_hex(fd, tmp->arg1, tmp->size[1])))
				malloc_error(fd, root);
			if (asml[tmp->cmd].arg_num > 1 && !(write_hex(fd, tmp->arg2, tmp->size[2])))
				malloc_error(fd, root);
			if (asml[tmp->cmd].arg_num > 2 && !(write_hex(fd, tmp->arg3, tmp->size[3])))
				malloc_error(fd, root);
		}
		tmp = tmp->next;
	}
}
