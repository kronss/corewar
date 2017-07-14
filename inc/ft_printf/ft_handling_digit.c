/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_digit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 22:20:09 by ochayche          #+#    #+#             */
/*   Updated: 2017/02/21 22:20:14 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	handling the %digit;
**	width -> precision -> chose specifire + precision -> (-)width -> (-)prec
*/

#include "ft_printf.h"

static char				ft_size_digit(long long digit)
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

static char				ft_strlen_digit(t_flist *lst, long long digit)
{
	char				res;
	char				tmp;

	tmp = 0;
	res = ft_size_digit(digit);
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
	if ((digit < 0) || (((lst->flags)[4] == '+' || (lst->flags)[5] == ' ') &&
	digit >= 0))
		res++;
	return (res);
}

static char				ft_print_digit(long long digit, t_flist *lst)
{
	char len;

	len = 0;
	if (digit == 0 && lst->precision == -2)
		return (0);
	if (-10 < digit && digit < 10)
		len += ft_print_char(ABS(digit) + '0');
	else
	{
		len += ft_print_digit(digit / 10, lst);
		len += ft_print_digit(digit % 10, lst);
	}
	return (len);
}

static short			ft_hend_digit(t_flist *lst, long long digit, int *len)
{
	if ((lst->flags)[2] == '0' && lst->precision == -1)
		(lst->flags)[0] = '0';
	lst->size = ft_strlen_digit(lst, digit);
	if (digit < 0 && lst->flags[0] == '0')
		*len += ft_print_char('-');
	else if (digit >= 0 && lst->flags[0] == '0' && lst->flags[4] == '+')
		*len += ft_print_char('+');
	else if (lst->flags[0] == '0' && lst->flags[5] == ' ')
		*len += ft_print_char(' ');
	while ((lst->flags)[3] != '-' && lst->width > (lst->size))
		(*len += ft_print_char((lst->flags)[0])) && lst->width--;
	if ((lst->flags)[4] == '+' && digit >= 0 && lst->flags[0] != '0')
		*len += ft_print_char('+');
	else if (digit < 0 && lst->flags[0] == ' ' && lst->flags[0] != '0')
		*len += ft_print_char('-');
	else if ((lst->flags)[5] == ' ' && digit >= 0 && lst->flags[0] != '0')
		*len += ft_print_char(' ');
	while (lst->precision != -1 && lst->precision > 0)
		(*len += ft_print_char('0')) && lst->precision--;
	*len += ft_print_digit(digit, lst);
	while (lst->width > lst->size && (lst->flags)[3] == '-')
		(*len += ft_print_char(' ')) && lst->width--;
	return (*len);
}

int						ft_handling_digit(t_flist *lst, void *digit)
{
	int len;

	len = 0;
	if (lst->spec == 'D')
		(ft_hend_digit(lst, (long)digit, &len));
	else if (lst->j)
		(ft_hend_digit(lst, (long long)digit, &len));
	else if (lst->ll)
		(ft_hend_digit(lst, (long long)digit, &len));
	else if (lst->z)
		(ft_hend_digit(lst, (size_t)digit, &len));
	else if (lst->l)
		(ft_hend_digit(lst, (long)digit, &len));
	else if (lst->h)
		(ft_hend_digit(lst, (short)digit, &len));
	else if (lst->hh)
		(ft_hend_digit(lst, (char)digit, &len));
	else
		(ft_hend_digit(lst, (int)digit, &len));
	return (len);
}
