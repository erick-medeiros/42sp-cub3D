/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_disp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:53:30 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/29 02:02:34 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__zero_c(char *buff, va_list ap);
int	__zero_s(char *buff, char *s);
int	__zero_p(char *buff, char *s);
int	__zero_id(char *buff, char *s);
int	__zero_ux(char *buff, char *s);

static int	__spec_cs(char spec, char *buff, va_list ap)
{
	char	*s;
	int		bw;

	bw = 0;
	if (spec == 'c')
	{
		if (ft_strlen(buff) > 1)
			return (__zero_c(buff, ap));
		return (ft_putchar(va_arg(ap, int)));
	}
	s = va_arg(ap, char *);
	if (!s && ft_strlen(buff) > 5)
	{
		bw += ft_putnstr(buff, ft_strlen(buff) - 6);
		bw += ft_putstr("(null)");
		return (bw);
	}
	if (!s)
		return (ft_putstr("(null)"));
	if (ft_strlen(buff) > ft_strlen(s))
		return (__zero_s(buff, s));
	return (ft_putstr(s));
}

static int	__spec_p(char *buff, va_list ap)
{
	char	*s;
	int		bw;

	bw = 0;
	s = __getstr('p', ap);
	if (*s == '0' && ft_strlen(buff) > 5)
	{
		free(s);
		bw += ft_putnstr(buff, ft_strlen(buff) - 5);
		bw += ft_putstr("(nil)");
		return (bw);
	}
	if (*s == '0')
	{
		free(s);
		return (ft_putstr("(nil)"));
	}
	if (ft_strlen(buff) > ft_strlen(s) + 2)
		return (__zero_p(buff, s));
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
			return (__zero_id(buff, s));
		bw = ft_putstr(s);
	}
	if (spec == 'u')
	{
		s = ft_utoa(va_arg(ap, unsigned int));
		if (ft_strlen(buff) > ft_strlen(s))
			return (__zero_ux(buff, s));
		bw = ft_putstr(s);
	}
	free(s);
	return (bw);
}

static int	__spec_hex(char spec, char *buff, va_list ap)
{
	char	*s;
	int		bw;

	s = __getstr(spec, ap);
	if (ft_strlen(buff) > ft_strlen(s))
		return (__zero_ux(buff, s));
	bw = ft_putstr(s);
	free(s);
	return (bw);
}

int	__zero_dispatch(char spec, char *buff, va_list ap)
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
