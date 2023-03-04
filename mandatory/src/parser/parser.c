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
#include "parser.h"

char	**get_map(int fd)
{
	char	**map;
	char	*row;
	char	*buff;
	char	*tmp;

	row = ft_gnl(fd);
	if (!row)
		return (NULL);
	while (is_reserved_ch(*row, "NSEWCF\n"))
		if (!is_row_empty(&row, fd))
			return (NULL);
	buff = ft_strdup("");
	while (row)
	{
		tmp = buff;
		buff = ft_strjoin(buff, row);
		free(tmp);
		free(row);
		row = ft_gnl(fd);
	}
	map = ft_split(buff, '\n');
	free(buff);
	return (map);
}

static void	calculate_map_size(t_game *game)
{
	int	width;

	if (!game->map)
		return ;
	game->map_width = 0;
	game->map_height = 0;
	while (game->map[game->map_height])
	{
		width = 0;
		while (game->map[game->map_height][width])
			width++;
		if (game->map_width < width)
			game->map_width = width;
		game->map_height++;
	}
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
		game->map = NULL;
		return (0);
	}
	calculate_map_size(game);
	if (!validate_map(game))
		return (0);
	// print_map(game->map);
	return (1);
}
