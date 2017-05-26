/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochayche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:00:15 by ochayche          #+#    #+#             */
/*   Updated: 2017/01/20 17:00:16 by ochayche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** conversions: % s S p d D i o O u U x X c C
** # 0 - + space
** the minimum field-width // 20
** precision // .10
** hh, h, l, ll, j, z
**[0] = default print char
**[1] = '#';
**[2] = '0';
**[3] = '-';
**[4] = '+';
**[5] = ' '; - space
*/

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>

# define ABS(x) ((x < 0) ? -(x) : (x))

typedef	struct	s_flist
{
	char		*flags;
	short		width;
	short		precision;
	char		hh;
	char		h;
	char		l;
	char		z;
	char		ll;
	char		j;
	char		spec;
	short		size;
}				t_flist;

int				ft_handling_char(t_flist *lst, void *c);
int				ft_handling_str(t_flist *lst, void *str);
int				ft_handling_digit(t_flist *lst, void *digit);
int				ft_handling_unsigned_digit(t_flist *lst, void *digit);
int				ft_handling_x(t_flist *lst, void *digit);
int				ft_handling_o(t_flist *lst, void *digit);
int				ft_handling_ptr(t_flist *lst, void *digit);
int				ft_print_char(int c);
int				ft_print_str(char *str, int precision);
char			ft_print_wchar(wchar_t wc);
int				ft_print_wstr(wchar_t *wstr, int precision);
int				ft_out(t_flist *list, va_list va);
int				ft_look_conversion(char **fmt, va_list va);
char			ft_strchr_f(char *s, int c);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *src);
int				ft_atoi_f(char **str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
int				ft_strlen(const char *s);
int				ft_print_percent(t_flist *lst, char c);
void			ft_strdel(char **as);
int				ft_printf(char *fmt, ...);

#endif
