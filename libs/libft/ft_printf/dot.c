/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:39:06 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 20:23:30 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	__dot_justify(int n, char spec, va_list ap)
{
	char	*buff;
	int		bw;

	bw = 0;
	buff = ft_calloc(n + 1, sizeof(char));
	if (!buff)
		return (0);
	ft_memset(buff, '0', n);
	if (ft_strchr("cspdiuxX", spec))
		bw += __dot_dispatch(spec, buff, ap);
	free(buff);
	return (bw);
}

static int	__dot_s(int n, va_list ap)
{
	char	*s;
	int		bw;

	bw = 0;
	s = va_arg(ap, char *);
	if (!s)
	{
		if (n > 5)
			return (ft_putstr("(null)"));
		return (ft_putstr(""));
	}
	if (n > (int)ft_strlen(s))
		bw += ft_putstr(s);
	else
		while (n--)
			bw += ft_putchar(*s++);
	return (bw);
}

int	__dot(const char **fmt, va_list ap)
{
	int		bw;
	int		n;

	++(*fmt);
	if (ft_isdigit(**fmt))
	{
		n = ft_atoi(*fmt);
		while (!ft_strchr("cspdiuxX%", **fmt))
			(*fmt)++;
		if (**fmt == 's')
			return (__dot_s(n, ap));
		return (__dot_justify(n, **fmt, ap));
	}
	else if (**fmt == 's')
	{
		while (!ft_strchr("cspdiuxX%", **fmt))
			(*fmt)++;
		return (0);
	}
	bw = __spec_dispatch(**fmt, ap);
	while (!ft_strchr("cspdiuxX%", **fmt))
		(*fmt)++;
	return (bw);
}
