/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:29 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/02 17:11:09 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_map_structure(t_game *game)
{
	char	*line;
	int		i;

	i = -1;
	while (++i < game->map_height)
	{
		line = ft_strtrim(game->map[i], " \n\t");
		if (ft_strlen(line) == 0)
		{
			if (line)
				free(line);
			continue ;
		}
		if (is_reserved_ch(*line, "NSWE"))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	print_map(game->map);

	int	i;
	int	j;

	if (!is_valid_map_structure(game))
		return (perr("[-] invalid map structure"));

	// top
	j = -1;
	while (game->map[0][++j])
	{
		if (game->map[0][j] == ' ')
			continue ;
		if (game->map[0][j] != '1')
			return (perr("[-] top border is not surrounded by walls"));
	}

	// left
	i = 0;
	while (++i < game->map_height - 1)
	{
		j = -1;
		while (game->map[i][++j] == ' ')
			continue ;
		if (game->map[i][j] != '1')
			return (perr("[-] left border is not surrounded by walls"));
	}

	// right
	i = 0;
	size_t	size;
	char	*row;
	while (++i < game->map_height - 1)
	{
		row = ft_strtrim(game->map[i], " \n\t");
		size = ft_strlen(row) - 1;
		j = -1;
		if (row[size] != '1')
		{
			free(row);
			return (perr("[-] right border is not surrounded by walls"));
		}
		free(row);
	}

	// bottom
	j = -1;
	while (game->map[game->map_height - 1][++j])
	{
		if (game->map[i][j] == ' ')
			continue ;
		if (game->map[i][j] != '1')
			return (perr("[-] bottom border is not surrounded by walls"));
	}
	return (1);
}
