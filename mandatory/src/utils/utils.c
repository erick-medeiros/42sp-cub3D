/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:33:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/04 17:21:57 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_reserved_ch(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

int	perr(const char *str)
{
	if (str)
		printf("%s\n", str);
	return (0);
}

void	clean_gnl(char *tmp, int fd)
{
	if (fd == -1)
		return ;
	free(tmp);
	tmp = ft_gnl(fd);
	while (tmp)
	{
		free(tmp);
		tmp = ft_gnl(fd);
	}
	close(fd);
}

int	is_digit_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

double	calcule_scale(int origin_width, int origin_height,
	int destination_width, int destination_height)
{
	double	width_proportion;
	double	height_proportion;

	width_proportion = (double) destination_width / origin_width;
	height_proportion = (double) destination_height / origin_height;
	if (width_proportion > height_proportion)
		return (height_proportion);
	else
		return (width_proportion);
}
