/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_disp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 02:25:25 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 20:06:59 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__dot_c(char *buff, va_list ap);
int	__dot_p(char *buff, char *s);
int	__dot_nve_id(char *buff, char *s);
int	__dot_uidx(char *buff, char *s);

static int	__spec_c(char *buff, va_list ap)
{
	char	ch;

	if (ft_strlen(buff) > 1)
		return (__dot_c(buff, ap));
	ch = va_arg(ap, int);
	if (!ch)
		return (ft_putstr(""));
	return (ft_putchar(ch));
}

static int	__spec_p(char *buff, va_list ap)
{
	char	*s;
	int		bw;

	s = ft_ultoa(va_arg(ap, unsigned long), "0123456789abcdef");
	if (ft_strlen(buff) > ft_strlen(s))
		return (__dot_p(buff, s));
	else if (*s == '0')
	{
		free(s);
		return (write(1, "(nil)", 5));
	}
	bw = ft_putstr("0x");
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
		if (s[0] == '-' && ft_strlen(buff) > ft_strlen(s) - 1)
			return (__dot_nve_id(buff, s));
		else if (ft_strlen(buff) > ft_strlen(s))
			return (__dot_uidx(buff, s));
		bw = ft_putstr(s);
		free(s);
		return (bw);
	}
	else if (spec == 'u')
	{
		s = ft_utoa(va_arg(ap, unsigned int));
		if (ft_strlen(buff) > ft_strlen(s))
			return (__dot_uidx(buff, s));
		bw = ft_putstr(s);
		free(s);
		return (bw);
	}
	return (bw);
}

static int	__spec_hex(char spec, char *buff, va_list ap)
{
	char	*s;
	int		bw;

	s = __getstr(spec, ap);
	if (ft_strlen(buff) > ft_strlen(s))
		return (__dot_uidx(buff, s));
	bw = ft_putstr(s);
	free(s);
	return (bw);
}

int	__dot_dispatch(char spec, char *buff, va_list ap)
{
	if (spec == 'c')
		return (__spec_c(buff, ap));
	if (spec == 'p')
		return (__spec_p(buff, ap));
	if (spec == 'd' || spec == 'i' || spec == 'u')
		return (__spec_uid(spec, buff, ap));
	if (spec == 'x' || spec == 'X')
		return (__spec_hex(spec, buff, ap));
	return (0);
}
