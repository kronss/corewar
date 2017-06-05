
#include "corewar.h"

static void			first_part(t_asml *asml, char *name, short arg_num, short cycles)
{
	size_t	i;
	
	i = 0;
	while (name[i])
	{
		asml->name[i] = name[i];
		i++;
	}
	while (i < 6)
	{
		asml->name[i] = '\0';
		i++;	
	}
	asml->arg_num = arg_num;
	asml->cycles = cycles;
}

static void			second_part(t_asml *asml, short label_size, short carry, short cod_oct)
{
	asml->label_size = label_size;
	asml->carry = carry;
	asml->cod_oct = cod_oct;
}

static void		asml_other(t_asml asml[16])
{
	first_part(&asml[8], "zjmp", 1, 20);
	second_part(&asml[8], 2, 0, 0);
	asml[8].arg_type = 128;
	first_part(&asml[9], "ldi", 3, 25);
	second_part(&asml[9], 2, 0, 0);
	asml[9].arg_type = 256 + 128 + 64 + 32 + 16 + 4;
	first_part(&asml[10], "sti", 3, 25);
	second_part(&asml[10], 2, 0, 0);
	asml[10].arg_type = 256 + 32 + 16 + 8 + 4 + 2;
	first_part(&asml[11], "fork", 1, 800);
	second_part(&asml[11], 2, 0, 0);
	asml[11].arg_type = 128;
	first_part(&asml[12], "lld", 2, 10);
	second_part(&asml[12], 4, 0, 0);
	asml[12].arg_type = 128 + 64 + 32;
	first_part(&asml[13], "lldi", 3, 50);
	second_part(&asml[13], 2, 0, 0);
	asml[13].arg_type = 256 + 128 + 64 + 32 + 16 + 4;
	first_part(&asml[14], "lfork", 1, 1000);
	second_part(&asml[14], 2, 0, 0);
	asml[14].arg_type = 128;
	first_part(&asml[15], "aff", 1, 2);
	second_part(&asml[15], 0, 0, 0);
	asml[15].arg_type = 256;
}

/* arg_type
**		 1 arg				 2 arg				 3 arg
** T_REG T_DIR T_IND | T_REG T_DIR T_IND | T_REG T_DIR T_IND
** ---------------------------------------------------------
**	 0     0	 0	 |	 0     0	 0	 |	 0     0	 0
** ---------------------------------------------------------
**	256	  128	64	 |	32	  16	 8	 |	 4	   2	 1
**
**	000 000 001 = 1
**	000 000 010 = 2
**	000 000 100 = 4
**
**	000 001 000 = 8
**	000 010 000 = 16
**	000 100 000 = 32
**
**	001 000 000 = 64
**	010 000 000 = 128
**	100	000	000 = 256
*/

void			asml_default(t_asml asml[16])
{
	first_part(&asml[0], "live", 1, 10);
	second_part(&asml[0], 4, 0, 0);
	asml[0].arg_type = 128;
	first_part(&asml[1], "ld", 2, 5);
	second_part(&asml[1], 4, 0, 0);
	asml[1].arg_type = 128 + 64 + 32;
	first_part(&asml[2], "st", 2, 5);
	second_part(&asml[2], 0, 0, 0);
	asml[2].arg_type = 256 + 32 + 8;
	first_part(&asml[3], "add", 3, 10);
	second_part(&asml[3], 0, 0, 0);
	asml[3].arg_type = 256 + 32 + 4;
	first_part(&asml[4], "sub", 3, 10);
	second_part(&asml[4], 0, 0, 0);
	asml[4].arg_type = 256 + 32 + 4;
	first_part(&asml[5], "and", 3, 6);
	second_part(&asml[5], 4, 0, 0);
	asml[5].arg_type = 256 + 128 + 64 + 32 + 16 + 8 + 4;
	first_part(&asml[6], "or", 3, 6);
	second_part(&asml[6], 4, 0, 0);
	asml[6].arg_type = 256 + 128 + 64 + 32 + 16 + 8 + 4;
	first_part(&asml[7], "xor", 3, 6);
	second_part(&asml[7], 4, 0, 0);
	asml[7].arg_type = 256 + 128 + 64 + 32 + 16 + 8 + 4;
	asml_other(asml);
}
