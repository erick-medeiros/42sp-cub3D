/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus_wr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 01:29:59 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:07:48 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__minus_c(char *buff, va_list ap)
{
	char	*temp;
	int		bw;
	int		c;

	bw = 0;
	c = va_arg(ap, int);
	if (!c)
	{
		bw = write(1, "", 1);
		temp = ft_calloc(ft_strlen(buff), sizeof(char));
		ft_memcpy(temp, buff, ft_strlen(buff) - 1);
		bw += ft_putstr(temp);
	}
	else
	{
		temp = ft_calloc(ft_strlen(buff) + 1, sizeof(char));
		ft_memcpy(temp, buff, ft_strlen(buff) + 1);
		temp[0] = c;
		bw += ft_putstr(temp);
	}
	free(temp);
	return (bw);
}

int	__minus_s(char *buff, char *s)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(ft_strlen(s) + delta + 1, sizeof(char));
	if (!*s)
		ft_memcpy(temp, buff, ft_strlen(buff) + 1);
	else
	{
		ft_memcpy(temp, s, ft_strlen(s) + 1);
		ft_strlcat(temp, buff, ft_strlen(temp) + delta + 1);
	}
	bw = ft_putstr(temp);
	free(temp);
	return (bw);
}

int	__minus_zero(char *buff, char *s)
{
	char	*temp;
	int		bw;

	if (ft_strlen(buff) > 5)
	{
		bw = ft_putstr("(nil)");
		temp = ft_calloc(ft_strlen(buff) + 1, sizeof(char));
		ft_memcpy(temp, buff, ft_strlen(buff) - 5);
		bw += ft_putstr(temp);
		free(temp);
		free(s);
		return (bw);
	}
	free(s);
	return (write(1, "(nil)", 5));
}

int	__minus_p(char *buff, char *s)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(2 + ft_strlen(s) + delta + 1, sizeof(char));
	ft_memcpy(temp, "0x", 3);
	ft_strlcat(temp, s, ft_strlen(temp) + ft_strlen(s) + 1);
	ft_strlcat(temp, buff, ft_strlen(temp) + (delta - 2) + 1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}

int	__minus_diux(char *buff, char *s)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(ft_strlen(s) + delta + 1, sizeof(char));
	ft_memcpy(temp, s, ft_strlen(s) + 1);
	ft_strlcat(temp, buff, ft_strlen(temp) + delta + 1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}
