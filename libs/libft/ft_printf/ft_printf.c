/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:53:54 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:07:05 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__spec_dispatch(char spec, va_list ap)
{
	if (spec == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (spec == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (spec == 'p')
		return (ft_putptr(va_arg(ap, void *)));
	if (spec == 'd' || spec == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	if (spec == 'u')
		return (ft_putunbr(va_arg(ap, unsigned int)));
	if (spec == 'x' || spec == 'X')
		return (ft_putnbr_hex(va_arg(ap, unsigned int), spec));
	if (spec == '%')
		return (write(1, "%", 1));
	return (0);
}

static int	__check_spec(const char **fmt, va_list ap)
{
	if (**fmt == '#')
		return (__sharp(fmt, ap));
	if (**fmt == '+')
		return (__plus(fmt, ap));
	if (**fmt == '-')
		return (__minus(fmt, ap));
	if (**fmt == '.')
		return (__dot(fmt, ap));
	if (**fmt == ' ')
		return (__space(fmt, ap));
	if (ft_isdigit(**fmt))
		return (__zero(ft_atoi(*fmt), fmt, ap));
	if (ft_strchr("cspdiuxX%", **fmt))
		return (__spec_dispatch(**fmt, ap));
	return (0);
}

int	ft_printf(const char *fmt, ...)
{
	int		bw;
	va_list	ap;

	va_start(ap, fmt);
	bw = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			++fmt;
			bw += __check_spec(&fmt, ap);
		}
		else
			bw += write(1, fmt, 1);
		fmt++;
	}
	va_end(ap);
	return (bw);
}
