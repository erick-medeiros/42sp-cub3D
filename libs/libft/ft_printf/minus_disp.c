/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus_disp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:32:31 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/29 02:01:42 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__minus_c(char *buff, va_list ap);
int	__minus_s(char *buff, char *s);
int	__minus_zero(char *buff, char *s);
int	__minus_p(char *buff, char *s);
int	__minus_diux(char *buff, char *s);

static int	__spec_cs(char spec, char *buff, va_list ap)
{
	char	*s;

	if (spec == 'c')
	{
		if (ft_strlen(buff) > 1)
			return (__minus_c(buff, ap));
		return (ft_putchar(va_arg(ap, int)));
	}
	if (spec == 's')
	{
		s = va_arg(ap, char *);
		if (ft_strlen(buff) > ft_strlen(s))
			return (__minus_s(buff, s));
		return (ft_putstr(s));
	}
	return (0);
}

static int	__spec_p(char *buff, va_list ap)
{
	char	*s;
	int		bw;

	bw = 0;
	s = __getstr('p', ap);
	if (*s == '0')
		return (__minus_zero(buff, s));
	else if (ft_strlen(buff) > ft_strlen(s) + 2)
		return (__minus_p(buff, s));
	bw += ft_putstr("0x");
	bw += ft_putstr(s);
	free(s);
	return (bw);
}

static int	__spec_uid(char spec, char *buff, va_list ap)
{
	char	*s;
	int		bw;

	bw = 0;
	if (spec == 'd' || spec == 'i')
	{
		s = ft_itoa(va_arg(ap, int));
		if (ft_strlen(buff) > ft_strlen(s))
			return (__minus_diux(buff, s));
		bw += ft_putstr(s);
	}
	if (spec == 'u')
	{
		s = ft_utoa(va_arg(ap, unsigned int));
		if (ft_strlen(buff) > ft_strlen(s))
			return (__minus_diux(buff, s));
		bw += ft_putstr(s);
	}
	free(s);
	return (bw);
}

static int	__spec_hex(char spec, char *buff, va_list ap)
{
	char	*s;
	int		bw;

	bw = 0;
	s = __getstr(spec, ap);
	if (ft_strlen(buff) > ft_strlen(s))
		return (__minus_diux(buff, s));
	bw += ft_putstr(s);
	free(s);
	return (bw);
}

int	__minus_dispatch(char spec, char *buff, va_list ap)
{
	if (spec == 'c' || spec == 's')
		return (__spec_cs(spec, buff, ap));
	if (spec == 'p')
		return (__spec_p(buff, ap));
	if (spec == 'd' || spec == 'i' || spec == 'u')
		return (__spec_uid(spec, buff, ap));
	if (spec == 'x' || spec == 'X')
		return (__spec_hex(spec, buff, ap));
	return (0);
}
