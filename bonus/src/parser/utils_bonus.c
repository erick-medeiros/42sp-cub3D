/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:54:54 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/13 19:32:19 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	**get_matrix(char *row)
{
	char	**matrix;
	int		i;

	matrix = NULL;
	if (ft_strchr(row, '\t'))
	{
		i = -1;
		while (row[++i])
			if (row[i] == '\t')
				row[i] = ' ';
	}
	matrix = ft_split(row, ' ');
	if (!matrix)
		return (NULL);
	return (matrix);
}

char	*get_filename(char *filename)
{
	if (!filename || ft_strncmp(filename, "\n", 2) == 0)
		return (NULL);
	return (ft_strdup(filename));
}

int	is_row_empty(char **row, int fd)
{
	free(*row);
	*row = ft_gnl(fd);
	if (!*row)
		return (0);
	return (1);
}

int	is_empty_line(char **row, int fd)
{
	if (**row != '\n')
		return (0);
	free(*row);
	*row = ft_gnl(fd);
	return (1);
}

int	get_width_map(int width, char *row)
{
	int	len;

	if (!row)
		return (width);
	len = ft_strlen(row);
	if (len == 0)
		return (width);
	if (row[len - 1] == '\n')
		len--;
	return(ft_max(width, len));
}
