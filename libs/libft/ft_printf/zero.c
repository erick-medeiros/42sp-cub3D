/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:35:52 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:08:31 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__zero(int n, const char **fmt, va_list ap)
{
	int		bw;
	char	*buff;

	bw = 0;
	buff = ft_calloc(n + 1, sizeof(char));
	if (!buff)
		return (0);
	if (**fmt == '0')
		ft_memset(buff, '0', n);
	else
		ft_memset(buff, ' ', n);
	while (!ft_strchr("cspdiuxX%", **fmt))
		++(*fmt);
	if (ft_strchr("cspdiuxX", **fmt))
		bw += __zero_dispatch(**fmt, buff, ap);
	free(buff);
	return (bw);
}
