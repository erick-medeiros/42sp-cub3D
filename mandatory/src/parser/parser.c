/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:31:37 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/13 19:29:53 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

char	*get_map(int fd, int *map_width, int *map_height)
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
	while (row)
	{
		if (ft_strlen(row) > 1)
			(*map_height)++;
		(*map_width) = get_width_map(*map_width, row);
		tmp = buff;
		buff = ft_strjoin(buff, row);
		free(tmp);
		free(row);
		row = ft_gnl(fd);
	}
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
		return (perr("exceeded maximum width"));
	}
	if (game->map_height > MAX_MAP_SIZE)
	{
		ft_free_matrix(game->map);
		game->map = NULL;
		return (perr("exceeded maximum height"));
	}
	return (1);
}

static void	find_player(t_game *game)
{
	int		x;
	int		y;
	t_bool	found;

	found = FALSE;
	y = 0;
	while (!found && y < game->map_height)
	{
		x = 0;
		while (!found && x < game->map_width)
		{
			if (is_reserved_ch(game->map[y][x], "NSWE"))
			{
				game->player.pos = create_vector(x, y);
				game->player.pos = add_vector(game->player.pos,
						create_vector(0.5, 0.5));
				player_orientation(&game->player, game->map[y][x]);
				found = TRUE;
			}
			x++;
		}
		y++;
	}
}

int	init_map(t_game *game, char **av)
{
	int		fd;
	char	*map_array;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perr("error while reading the map"));
	game->map_width = 0;
	game->map_height = 0;
	map_array = start_map(game, fd);
	close(fd);
	if (!map_array)
		return (perr("empty map"));
	game->map = split_map(map_array, game->map_width);
	if (!game->map)
		return (perr("empty map"));
	if (!check_map_sizes(game))
		return (0);
	if (!validate_map_attributes(game->map))
		return (clean_map(game));
	if (!validate_map(game, av[1]))
		return (clean_map(game));
	find_player(game);
	return (1);
}
