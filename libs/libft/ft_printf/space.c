/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:04:49 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:08:11 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	__space_justify(int n, const char **fmt, va_list ap)
{
	int		bw;
	char	*buff;

	bw = 0;
	buff = ft_calloc(n + 1, sizeof(char));
	if (!buff)
		return (0);
	ft_memset(buff, ' ', n);
	while (!ft_strchr("cspdiuxX", **fmt))
		++(*fmt);
	if (ft_strchr("cspdiuxX", **fmt))
		bw += __space_dispatch(**fmt, buff, ap);
	free(buff);
	return (bw);
}

static int	__space_single(va_list ap)
{
	int		bw;
	char	*s;

	bw = 0;
	s = ft_itoa(va_arg(ap, int));
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

int	__space(const char **fmt, va_list ap)
{
	int		bw;

	++(*fmt);
	bw = 0;
	if (**fmt == 's')
		return (__spec_dispatch('s', ap));
	if (ft_isdigit(**fmt))
		bw += __space_justify(ft_atoi(*fmt), fmt, ap);
	else
		bw += __space_single(ap);
	while (!ft_strchr("cspdiuxX%", **fmt))
		++(*fmt);
	return (bw);
}
