/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_wchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 18:11:22 by ochayche          #+#    #+#             */
/*   Updated: 2017/02/08 18:11:23 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char					size_wchar(unsigned int wc)
{
	if (wc <= 127)
		return (1);
	else if (wc >= 128 && wc <= 2047)
		return (2);
	else if (wc >= 2048 && wc <= 65535)
		return (3);
	else if (wc >= 65536 && wc <= 2097151)
		return (4);
	else
		return (0);
}

char						ft_print_wchar(wchar_t wc)
{
	char					res;
	char					size;
	unsigned char			curr_byte;

	res = 0;
	size = size_wchar(wc);
	if (size == 1)
		return (ft_print_char(wc));
	curr_byte = (240 << (4 - size)) | (wc >> ((size - 1) * 6));
	res += ft_print_char(curr_byte);
	size--;
	while (size--)
	{
		curr_byte = ((wc >> ((size) * 6)) & 63) | 128;
		res += ft_print_char(curr_byte);
	}
	return (res);
}
