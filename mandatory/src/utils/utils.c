/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:33:15 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 12:08:21 by frosa-ma         ###   ########.fr       */
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

int	perr(char *str)
{
	char	*capitalized;
	char	*err_msg;

	if (!str)
		return (0);
	capitalized = malloc(2);
	capitalized[0] = ft_toupper(*str);
	capitalized[1] = 0;
	err_msg = ft_strjoin(capitalized, str + 1);
	printf("Error\n%s\n", err_msg);
	free(capitalized);
	free(err_msg);
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
