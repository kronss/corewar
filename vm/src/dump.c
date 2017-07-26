/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abykov <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:33:07 by abykov            #+#    #+#             */
/*   Updated: 2017/06/07 11:33:08 by abykov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#define FBLACK      "\033[30;"
#define FRED        "\033[31;"
#define FGREEN      "\033[32;"
#define FBLUE       "\033[34;"
#define FWHITE      "\033[7;"
#define FCYAN       "\033[36;"
#define BBLACK      "40m"
#define BRED        "41m"
#define BGREEN      "42m"
#define BBLUE       "44m"
#define BCYAN	    "46m"
#define BWHITE      "47m"
#define BORDER		FWHITE BWHITE
#define RED			FRED BBLACK
#define GREEN		FGREEN BBLACK
#define BLUE		FBLUE BBLACK
#define CYAN		FCYAN BBLACK
#define PCRED		FBLACK BRED
#define PCGREEN		FBLACK BGREEN
#define PCBLUE		FBLACK BBLUE
#define PCCYAN		FBLACK BCYAN
#define PCWHITE		FBLACK BWHITE
#define NONE        "\033[0m"
#define TOP1  		BORDER "***************************************************"
#define TOP2		"********************************* https://www.redtube.com/"
#define TOP3		"174545 ***************************************************"
#define TOP4		"*****************************************" NONE "\n"
#define TOP5		BORDER "*" NONE "          " BORDER "*" NONE "             "
#define TOP6		"                                                          "
#define TOP7		"                                                          "
#define TOP8		"                                                          "
#define TOP9		"        " BORDER "*" NONE "\n"
#define BOT1		"  " BORDER "*" NONE "\n" BORDER "*" NONE "          "
#define BOT2		BORDER "*" NONE "                                          "
#define BOT3		"                                                          "
#define BOT4		"                                                          "
#define BOT5		"                                     " BORDER "*" NONE "\n"
#define BOT6		BORDER "***************************************************"
#define BOT7		"**********************************************************"
#define BOT8		"**********************************************************"
#define BOT9		"*****************************************" NONE "\n"
#define TOP			TOP1 TOP2 TOP3 TOP4 TOP5 TOP6 TOP7 TOP8 TOP9
#define BOT			BOT1 BOT2 BOT3 BOT4 BOT5 BOT6 BOT7 BOT8 BOT9

/*
** 0 0 0 0 1 [0 0 0] <-- RGBC
**         ^
**    PC INDICATOR
*/

void			print_colored_byte(t_uchar i, t_uchar byte)
{
	if (i == 1)
		ft_printf(GREEN "%0.2hhx" NONE, byte);
	else if (i == 2)
		ft_printf(BLUE "%0.2hhx" NONE, byte);
	else if (i == 3)
		ft_printf(RED "%0.2hhx" NONE, byte);
	else if (i == 4)
		ft_printf(CYAN "%0.2hhx" NONE, byte);
	else if (i == 5)
		ft_printf("%0.2hhx", byte);
	else if (i == 9)
		ft_printf(PCGREEN "%0.2hhx" NONE, byte);
	else if (i == 10)
		ft_printf(PCBLUE "%0.2hhx" NONE, byte);
	else if (i == 11)
		ft_printf(PCRED "%0.2hhx" NONE, byte);
	else if (i == 12)
		ft_printf(PCCYAN "%0.2hhx" NONE, byte);
	else if (i == 13)
		ft_printf(PCWHITE "%0.2hhx" NONE, byte);
}

void			dump(t_data *data)
{
	size_t		i;

	ft_printf(TOP);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf(BORDER "*" NONE "  0x0000  " BORDER "*" NONE "  ");
		else if (i % 64 == 0)
			ft_printf("  " BORDER "*" NONE "\n" BORDER "*" NONE
						"  %#.4x  " BORDER "*" NONE "  ", (t_uint)i);
		else
			ft_printf(" ");
		print_colored_byte(data->color[i], data->map[i]);
		++i;
	}
	ft_printf(BOT);
}
