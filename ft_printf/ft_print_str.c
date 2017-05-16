/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:56:06 by ochayche          #+#    #+#             */
/*   Updated: 2017/01/25 12:56:07 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_print_str(char *str, int precision)
{
	int					len;

	len = 0;
	if (str == NULL)
		return (ft_print_str("(null)", precision));
	while (*str != '\0' && precision--)
	{
		len += ft_print_char(*str);
		str++;
	}
	return (len);
}
