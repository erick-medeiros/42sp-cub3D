/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:31:16 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:07:52 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__minus(const char **fmt, va_list ap)
{
	char	*buff;
	int		bw;
	int		n;

	++(*fmt);
	bw = 0;
	if (ft_isdigit(**fmt))
	{
		n = ft_atoi(*fmt);
		buff = ft_calloc(n + 1, sizeof(char));
		if (!buff)
			return (0);
		ft_memset(buff, ' ', n);
		while (!ft_strchr("cspdiuxX%", **fmt))
			++(*fmt);
		if (ft_strchr("cspdiuxX", **fmt))
			bw += __minus_dispatch(**fmt, buff, ap);
		free(buff);
		return (bw);
	}
	while (!ft_strchr("cspdiuxX%", **fmt))
		++(*fmt);
	if (ft_strchr("cspdiuxX", **fmt))
		bw += __spec_dispatch(**fmt, ap);
	return (bw);
}
