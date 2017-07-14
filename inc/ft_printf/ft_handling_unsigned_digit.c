/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_unsigned_digit.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 17:08:22 by ochayche          #+#    #+#             */
/*   Updated: 2017/02/24 17:08:28 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char				ft_size_uns_digit(unsigned long long digit)
{
	char				res;

	res = 1;
	digit /= 10;
	while (digit)
	{
		digit /= 10;
		res++;
	}
	return (res);
}

static char				ft_strlen_uns_digit(t_flist *lst, long long digit)
{
	char				res;
	char				tmp;

	tmp = 0;
	res = ft_size_uns_digit(digit);
	if (lst->precision != -1 && lst->precision > res)
	{
		tmp = (lst->precision - res);
		res = lst->precision;
	}
	if (tmp > 0)
		lst->precision = tmp;
	else if (digit == 0 && lst->precision == 0)
	{
		lst->precision = -2;
		res = 0;
	}
	else
		lst->precision = -1;
	return (res);
}

static char				ft_print_uns_digit(uintmax_t digit, t_flist *lst)
{
	char				len;

	len = 0;
	if (digit == 0 && lst->precision == -2)
		return (0);
	if (digit >= 10)
	{
		len += ft_print_uns_digit(digit / 10, lst);
		len += ft_print_char((digit % 10) + '0');
	}
	else
		len += ft_print_char(digit + '0');
	return (len);
}

static char				ft_hend_uns_digit(t_flist *lst, uintmax_t digit)
{
	short				len;

	len = 0;
	if ((lst->flags)[2] == '0' && lst->precision == -1)
		(lst->flags)[0] = '0';
	lst->size = ft_strlen_uns_digit(lst, digit);
	while ((lst->flags)[3] != '-' && lst->width > (lst->size))
		(len += ft_print_char((lst->flags)[0])) && lst->width--;
	while (lst->precision != -1 && lst->precision > 0)
		(len += ft_print_char('0')) && lst->precision--;
	len += ft_print_uns_digit(digit, lst);
	while (lst->width > lst->size && (lst->flags)[3] == '-')
		(len += ft_print_char(' ')) && lst->width--;
	return (len);
}

int						ft_handling_unsigned_digit(t_flist *lst, void *digit)
{
	if (lst->spec == 'U')
		return (ft_hend_uns_digit(lst, (unsigned long)digit));
	else if (lst->j)
		return (ft_hend_uns_digit(lst, (unsigned long long)digit));
	else if (lst->ll)
		return (ft_hend_uns_digit(lst, (unsigned long long)digit));
	else if (lst->z)
		return (ft_hend_uns_digit(lst, (size_t)digit));
	else if (lst->l)
		return (ft_hend_uns_digit(lst, (unsigned long)digit));
	else if (lst->h)
		return (ft_hend_uns_digit(lst, (unsigned short)digit));
	else if (lst->hh)
		return (ft_hend_uns_digit(lst, (unsigned char)digit));
	else
		return (ft_hend_uns_digit(lst, (unsigned int)digit));
}
