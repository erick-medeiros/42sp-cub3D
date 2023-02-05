/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_wr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 03:54:55 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 20:44:23 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__zero_c(char *buff, va_list ap)
{
	char	ch;
	int		bw;

	bw = 0;
	ch = va_arg(ap, int);
	if (!ch)
	{
		bw += ft_putnstr(buff, ft_strlen(buff) - 1);
		bw += ft_putchar('\0');
		return (bw);
	}
	bw += ft_putnstr(buff, ft_strlen(buff) - 1);
	bw += ft_putchar(ch);
	return (bw);
}

int	__zero_s(char *buff, char *s)
{
	int		bw;

	bw = 0;
	if (!*s)
		return (ft_putnstr(buff, ft_strlen(buff)));
	bw += ft_putnstr(buff, ft_strlen(buff) - ft_strlen(s));
	bw += ft_putstr(s);
	return (bw);
}

int	__zero_p(char *buff, char *s)
{
	size_t	delta;
	int		bw;

	bw = 0;
	delta = ft_strlen(buff) - ft_strlen(s) - 2;
	bw += ft_putnstr(buff, delta);
	bw += ft_putstr("0x");
	bw += ft_putstr(s);
	free(s);
	return (bw);
}

int	__zero_id(char *buff, char *s)
{
	size_t	delta;
	int		bw;

	bw = 0;
	delta = ft_strlen(buff) - ft_strlen(s);
	if (*s == '-' && *buff == '0')
	{
		bw += ft_putchar('-');
		bw += ft_putnstr(buff, delta);
		bw += ft_putstr(s + 1);
		free(s);
		return (bw);
	}
	if (*s == '-')
	{
		bw += ft_putnstr(buff, delta);
		bw += ft_putchar('-');
		bw += ft_putstr(s + 1);
		free(s);
		return (bw);
	}
	bw += ft_putnstr(buff, delta);
	bw += ft_putstr(s);
	free(s);
	return (bw);
}

int	__zero_ux(char *buff, char *s)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(ft_strlen(s) + delta + 1, sizeof(char));
	ft_memcpy(temp, buff, delta);
	ft_strlcat(temp, s, -1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}
