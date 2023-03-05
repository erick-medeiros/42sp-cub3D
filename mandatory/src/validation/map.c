/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:29 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/05 17:15:18 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	there_is_line_yet(int n, char *filepath)
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
	if (row)
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

int	validate_map_lines(t_game *game, char *filepath)
{
	char	*row;
	int		fd;
	int		n;

	game = game;
	fd = open(filepath, O_RDONLY);
	if (!fd)
		return (0);
	n = 0;
	row = ft_gnl(fd);
	n++;
	if (!row)
	{
		close(fd);
		return (0);
	}
	while (row)
	{
		if (is_reserved_ch(*row, "1 "))
			break ;
		free(row);
		row = ft_gnl(fd);
		n++;
	}
	while (row)
	{
		if (ft_strlen(row) == 1 && !ft_strncmp(row, "\n", 2))
		{
			free(row);
			row = ft_gnl(fd);
			n++;
			if (!row)
				return (1);
			if (there_is_line_yet(n, filepath))
			{
				if (ft_strlen(row) == 1 && !ft_strncmp(row, "\n", 2))
				{
					clean_gnl(row, fd);
					return (perr("[-] empty line detected"));
				}
			}

			if (ft_strlen(row) > 2)
			{
				clean_gnl(row, fd);
				return (perr("[-] empty line detected"));
			}
		}
		free(row);
		row = ft_gnl(fd);
		n++;
	}
	clean_gnl(row, fd);
	return (1);
}

int	validate_horizontal_inner(t_game *game)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = -1;
	while (game->map[++i])
		if (game->map[i][0] != '\n')
			len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == ' ' && game->map[i + 1][j] == ' ')
				continue ;
			if (game->map[i][j] == ' ' && game->map[i + 1][j] != '1')
			{
				if (is_reserved_ch(game->map[i + 1][j], "0NSWE"))
					return (perr("[-] invalid border"));
			}
			else if (is_reserved_ch(game->map[i][j], "0NSWE"))
			{
				if (game->map[i + 1][j] == ' ')
					return (perr("[-] invalid border"));
			}
		}
	}
	return (1);
}

int	validate_vertical_inner(t_game *game)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = -1;
	while (game->map[++i])
		if (game->map[i][0] != '\n')
			len++;
	i = 0;
	while (++i < len - 1)
	{
		j = -1;
		while (++j < game->map_width - 1)
		{
			if (game->map[i][j] == ' ' && game->map[i][j + 1] == ' ')
				continue ;
			if (game->map[i][j] == ' ' && game->map[i][j + 1] != '1')
			{
				if (is_reserved_ch(game->map[i][j + 1], "0NSWE"))
					return (perr("[-] invalid border"));
			}
			else if (is_reserved_ch(game->map[i][j], "0NSWE"))
			{
				if (game->map[i][j + 1] == ' ')
					return (perr("[-] invalid border"));
			}
		}
	}
	return (1);
}

int	validate_map(t_game *game, char *filepath)
{
	if (!validate_map_lines(game, filepath))
		return (0);
	if (!validate_sides(game))
		return (0);
	if (!validate_horizontal_inner(game))
		return (0);
	if (!validate_vertical_inner(game))
		return (0);
	return (1);
}
