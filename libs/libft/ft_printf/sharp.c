/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:01:19 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/29 02:02:22 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	__sharp_justify(char *buff, char *s, char spec)
{
	char	*temp;
	size_t	delta;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(2 + ft_strlen(s) + delta + 1, sizeof(char));
	ft_memcpy(temp, buff, delta - 2);
	if (spec == 'x')
		ft_strlcat(temp, "0x", ft_strlen(temp) + 3);
	else
		ft_strlcat(temp, "0X", ft_strlen(temp) + 3);
	ft_strlcat(temp, s, ft_strlen(temp) + ft_strlen(s) + 1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}

static int	__sharp_hex(char spec, char *s)
{
	int	bw;

	if (s[0] == '0')
	{
		free(s);
		return (write(1, "0", 1));
	}
	if (spec == 'x')
		bw = write(1, "0x", 2);
	else
		bw = write(1, "0X", 2);
	bw += ft_putstr(s);
	free(s);
	return (bw);
}

static int	__sharp_dispatch(char spec, char *buff, va_list ap)
{
	char	*s;

	s = __getstr(spec, ap);
	if (s[0] == '0')
	{
		free(s);
		return (write(1, "0", 1));
	}
	if (ft_strlen(buff) > ft_strlen(s) + 2)
		return (__sharp_justify(buff, s, spec));
	return (__sharp_hex(spec, s));
}

int	__sharp(const char **fmt, va_list ap)
{
	char	*buff;
	int		bw;
	int		n;

	++(*fmt);
	if (ft_isdigit(**fmt))
	{
		n = ft_atoi(*fmt);
		buff = ft_calloc(n + 1, sizeof(char));
		if (!buff)
			return (0);
		ft_memset(buff, ' ', n);
		while (!ft_strchr("cspdiuxX", **fmt))
			++(*fmt);
		bw = __sharp_dispatch(**fmt, buff, ap);
		free(buff);
		return (bw);
	}
	return (__sharp_hex(**fmt, __getstr(**fmt, ap)));
}
