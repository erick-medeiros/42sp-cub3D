/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_disp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:27:49 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:08:03 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__space_c(char *buff, va_list ap);
int	__space_spx(char *buff, char *s);
int	__space_uid(char *buff, char *s);

static int	__spec_cs(char spec, char *buff, va_list ap)
{
	char	*s;

	if (spec == 'c')
	{
		if (ft_strlen(buff) > 1)
			return (__space_c(buff, ap));
		return (ft_putchar(va_arg(ap, int)));
	}
	else if (spec == 's')
	{
		s = va_arg(ap, char *);
		if (ft_strlen(buff) > ft_strlen(s))
			return (__space_spx(buff, s));
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
	if (ft_strlen(buff) > ft_strlen(s))
		return (__space_spx(buff, s));
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
			return (__space_uid(buff, s));
		if (s[0] == '-')
			bw += ft_putstr(s);
		else
		{
			bw += write(1, " ", 1);
			bw += ft_putstr(s);
		}
		free(s);
		return (bw);
	}
	s = ft_utoa(va_arg(ap, unsigned int));
	if (ft_strlen(buff) > ft_strlen(s))
		return (__space_uid(buff, s));
	bw += ft_putstr(s);
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
		return (__space_spx(buff, s));
	bw += ft_putstr(s);
	free(s);
	return (bw);
}

int	__space_dispatch(char spec, char *buff, va_list ap)
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
