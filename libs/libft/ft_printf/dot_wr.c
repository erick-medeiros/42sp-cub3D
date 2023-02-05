/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_wr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 02:29:33 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/05/27 19:07:14 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	__dot_c(char *buff, va_list ap)
{
	char	*temp;
	int		bw;

	temp = ft_calloc(ft_strlen(buff) + 1, sizeof(char));
	ft_memcpy(temp, buff, ft_strlen(buff));
	temp[ft_strlen(temp) - 1] = va_arg(ap, int);
	bw = ft_putstr(temp);
	free(temp);
	return (bw);
}

int	__dot_p(char *buff, char *s)
{
	size_t	delta;
	char	*temp;
	int		bw;

	if (*s == '0')
	{
		free(s);
		return (write(1, "(nil)", 5));
	}
	delta = ft_strlen(buff) - ft_strlen(s) + 2;
	temp = ft_calloc(2 + ft_strlen(s) + delta + 1, sizeof(char));
	ft_memcpy(temp, "0x", 3);
	ft_strlcat(temp, buff, ft_strlen(temp) + (delta - 2) + 1);
	ft_strlcat(temp, s, ft_strlen(temp) + ft_strlen(s) + 1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}

int	__dot_nve_id(char *buff, char *s)
{
	size_t	delta;
	char	*temp;
	int		bw;

	delta = ft_strlen(buff) - ft_strlen(s);
	temp = ft_calloc(ft_strlen(s) + delta + 2, sizeof(char));
	temp[0] = '-';
	ft_strlcat(temp, buff, ft_strlen(temp) + delta + 2);
	ft_strlcat(temp, s + 1, -1);
	bw = ft_putstr(temp);
	free(temp);
	free(s);
	return (bw);
}

int	__dot_uidx(char *buff, char *s)
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
