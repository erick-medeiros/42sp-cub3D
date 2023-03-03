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

static char	*get_map(int fd, int *map_width, int *map_height)
{
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
	*map_width = 0;
	*map_height = 0;
	while (row)
	{
		(*map_height)++;
		(*map_width) = fmaxf(*map_width, ft_strlen(row));
		tmp = buff;
		buff = ft_strjoin(buff, row);
		free(tmp);
		free(row);
		row = ft_gnl(fd);
	}
	(*map_width) = fmaxf(*map_width - 1, 0);
	return (buff);
}

static char	**split_map(char *map_array, int map_width)
{
	char	**map;
	char	*line;
	int		i;

	map = ft_split(map_array, '\n');
	if (!map)
		return (NULL);
	i = 0;
	while (map[i])
	{
		line = map[i];
		map[i] = malloc((map_width + 1) * sizeof(char));
		if (!map[i])
			return (NULL);
		map[i][map_width] = '\0';
		ft_memset(map[i], ' ', map_width);
		ft_memcpy(map[i], line, ft_strlen(line));
		free(line);
		i++;
	}
	free(map_array);
	return (map);
}

int	check_map_sizes(t_game *game)
{
	if (game->map_width > MAX_MAP_SIZE)
	{
		ft_free_matrix(game->map);
		game->map = NULL;
		return (perr("[-] exceeded maximum width"));
	}
	if (game->map_height > MAX_MAP_SIZE)
	{
		ft_free_matrix(game->map);
		game->map = NULL;
		return (perr("[-] exceeded maximum height"));
	}
	return (1);
}

int	init_map(t_game *game, char **av)
{
	int		fd;
	char	*map_array;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perr("[-] error while reading the map"));
	map_array = get_map(fd, &game->map_width, &game->map_height);
	if (!map_array)
		return (perr("[-] empty map"));
	game->map = split_map(map_array, game->map_width);
	close(fd);
	if (!game->map)
		return (perr("[-] empty map"));
	if (!check_map_sizes(game))
		return (0);
	if (!is_valid_map(game->map))
	{
		ft_free_matrix(game->map);
		game->map = NULL;
		return (0);
	}
	print_map(game->map);
	return (1);
}
