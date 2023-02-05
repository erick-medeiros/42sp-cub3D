/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:15:02 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:07:56 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	__putnve(char *buff, char *s, int zero)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(ft_strlen(s) + delta + 1, sizeof(char));
	if (zero)
	{
		bw = write(1, "-", 1);
		ft_memcpy(temp, buff, delta);
		ft_strlcat(temp, s + 1, -1);
		bw += ft_putstr(temp);
		free(temp);
		free(s);
		return (bw);
	}
	ft_memcpy(temp, buff, delta);
	ft_strlcat(temp, s, -1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}

static int	__putpve(char *buff, char *s, int zero)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s) - 1;
	temp = ft_calloc(ft_strlen(s) + delta + 1, sizeof(char));
	if (zero)
	{
		bw = write(1, "+", 1);
		ft_memcpy(temp, buff, delta);
		ft_strlcat(temp, s, -1);
		bw += ft_putstr(temp);
		free(temp);
		free(s);
		return (bw);
	}
	ft_memcpy(temp, buff, delta);
	ft_strlcat(temp, "+", ft_strlen(temp) + 2);
	ft_strlcat(temp, s, -1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}

static int	__plus_dispatch(char *buff, va_list ap, int zero)
{
	char	*s;
	int		bw;

	bw = 0;
	s = ft_itoa(va_arg(ap, int));
	if (s[0] == '-' && ft_strlen(buff) > ft_strlen(s))
		return (__putnve(buff, s, zero));
	else if (ft_strlen(buff) > ft_strlen(s))
		return (__putpve(buff, s, zero));
	if (s[0] == '-')
		bw += ft_putstr(s);
	else
	{
		bw += write(1, "+", 1);
		bw += ft_putstr(s);
	}
	free(s);
	return (bw);
}

static int	__plus_justify(int n, const char **fmt, va_list ap, int zero)
{
	int		bw;
	char	*buff;

	bw = 0;
	buff = ft_calloc(n + 1, sizeof(char));
	if (!buff)
		return (0);
	if (zero)
		ft_memset(buff, '0', n);
	else
		ft_memset(buff, ' ', n);
	while (!ft_strchr("cspdiuxX%", **fmt))
		++(*fmt);
	if (ft_strchr("di", **fmt))
		bw += __plus_dispatch(buff, ap, zero);
	free(buff);
	return (bw);
}

int	__plus(const char **fmt, va_list ap)
{
	int		zero;
	int		bw;
	int		n;

	++(*fmt);
	bw = 0;
	if (ft_isdigit(**fmt))
	{
		zero = 0;
		if (**fmt == '0')
			zero = 1;
		n = ft_atoi(*fmt);
		while (!ft_strchr("cspdiuxX%", **fmt))
			(*fmt)++;
		return (__plus_justify(n, fmt, ap, zero));
	}
	n = va_arg(ap, int);
	if (n >= 0)
	{
		bw += write(1, "+", 1);
		bw += ft_putnbr(n);
	}
	else
		bw += ft_putnbr(n);
	return (bw);
}
