/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rows_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:40:26 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	verify_map_remaining_rows(int n, char *filepath)
{
	char	*row;
	int		fd;

	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	row = ft_gnl(fd);
	while (n--)
	{
		free(row);
		row = ft_gnl(fd);
	}
	if (!row)
		return (0);
	while (row)
	{
		if (ft_strlen(row) != 1 && is_reserved_ch(*row, "1 "))
		{
			clean_gnl(row, fd);
			return (1);
		}
		free(row);
		row = ft_gnl(fd);
	}
	return (0);
}

static int	validate_empty_rows(char **row, int *n, int fd, char *filepath)
{
	if (ft_strlen(*row) == 1 && !ft_strncmp(*row, "\n", 2))
	{
		free(*row);
		*row = ft_gnl(fd);
		(*n)++;
		if (!*row)
			return (1);
		if (verify_map_remaining_rows(*n, filepath))
		{
			if (ft_strlen(*row) == 1 && !ft_strncmp(*row, "\n", 2))
			{
				clean_gnl(*row, fd);
				return (perr("empty line detected"));
			}
		}
		if (ft_strlen(*row) > 2)
		{
			clean_gnl(*row, fd);
			return (perr("empty line detected"));
		}
	}
	return (1);
}

static void	displace_row(char **row, int *n, int fd)
{
	while (*row)
	{
		if (is_reserved_ch(**row, "1 "))
			break ;
		free(*row);
		*row = ft_gnl(fd);
		(*n)++;
	}
}

int	validate_map_lines(char *filepath)
{
	char	*row;
	int		fd;
	int		n;

	n = 0;
	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	row = ft_gnl(fd);
	n++;
	if (!row)
		return (close(fd), 0);
	displace_row(&row, &n, fd);
	while (row)
	{
		if (!validate_empty_rows(&row, &n, fd, filepath))
			return (0);
		free(row);
		row = ft_gnl(fd);
		n++;
	}
	clean_gnl(row, fd);
	return (1);
}
