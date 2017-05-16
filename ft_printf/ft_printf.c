/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 12:13:09 by ochayche          #+#    #+#             */
/*   Updated: 2017/01/19 12:13:18 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_printf(char *fmt, ...)
{
	int					len;
	va_list				va;

	len = 0;
	va_start(va, fmt);
	while (*fmt != '\0')
	{
		if (*fmt != '%')
			len += ft_print_char(*fmt);
		else
		{
			fmt++;
			len += ft_look_conversion(&(fmt), va);
		}
		fmt++;
	}
	va_end(va);
	return (len);
}
