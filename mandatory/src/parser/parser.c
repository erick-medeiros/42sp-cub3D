/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:31:37 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/02/05 12:44: by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_attribute(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!is_reserved_ch(map[i][j], "01 NSEW\n"))
				return (0);
	}
	return (1);
}

static int	is_player_found(char **map)
{
	int	player;
	int	i;
	int	j;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (is_reserved_ch(map[i][j], "NSEW"))
				player++;
	}
	if (player != 1)
		return (0);
	return (1);
}

static int	is_valid_map(char **map)
{
	if (!is_player_found(map))
		return (perr("[-] invalid number of players"));
	if (!is_valid_map_attribute(map))
		return (perr("[-] invalid map attribute"));
	return (1);
}

// HINT: we could make it not private eventually (if necessary)
static char	**get_map(int fd)
{
	char	**map;
	char	*row;
	char	*buff;

	row = ft_gnl(fd);
	while (is_reserved_ch(*row, "NSEWCF\n"))
	{
		free(row);
		row = ft_gnl(fd);
		if (!row)
			return (NULL);
	}
	buff = ft_strdup("");
	while (row)
	{
		buff = ft_strjoin(buff, row);
		free(row);
		row = ft_gnl(fd);
	}
	map = ft_split(buff, '\n');
	free(buff);
	return (map);
}

int	init_map(t_game *game, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perr("[-] error while reading the map"));
	game->map = get_map(fd);
	close(fd);
	if (!game->map)
		return (perr("[-] empty map"));
	if (!is_valid_map(game->map))
	{
		ft_free_matrix(game->map);
		return (0);
	}
	debug_map(game->map);
	return (1);
}
