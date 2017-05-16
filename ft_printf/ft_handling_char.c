/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 12:46:22 by ochayche          #+#    #+#             */
/*   Updated: 2017/02/18 12:46:23 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	handling the %char;
*/

#include "ft_printf.h"

int					ft_handling_char(t_flist *lst, void *c)
{
	int				len;

	len = 0;
	if ((lst->flags)[2] == '0')
		(lst->flags)[0] = '0';
	if ((lst->flags)[3] != '-' && lst->width > 1)
		while (((lst->width)-- - 1))
			len += ft_print_char((lst->flags)[0]);
	if (lst->spec == 'c' && !lst->l)
		len += ft_print_char((int)c);
	else if (lst->spec == 'C' || (lst->spec == 'c' && lst->l))
		len += ft_print_char((int)c);
	else
		len += ft_print_char(lst->spec);
	if (lst->width > 1 && (lst->flags)[3] == '-')
		while ((lst->width)-- - 1)
			len += ft_print_char(' ');
	return (len);
}
