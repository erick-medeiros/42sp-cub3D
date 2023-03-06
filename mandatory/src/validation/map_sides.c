/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_sides.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 14:56:34 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/06 12:54:51 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_top(t_game *game)
{
	int	j;

	j = -1;
	while (game->map[0][++j])
	{
		if (game->map[0][j] == ' ')
			continue ;
		if (game->map[0][j] != '1')
			return (perr("top border is not surrounded by walls"));
	}
	return (1);
}

static int	is_valid_left(t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = get_map_size(game);
	while (++i < len - 1)
	{
		j = -1;
		while (game->map[i][++j] == ' ')
			continue ;
		if (!game->map[i][j])
			continue ;
		if (game->map[i][j] != '1')
			return (perr("left border is not surrounded by walls"));
	}
	return (1);
}

static int	is_valid_right(t_game *game)
{
	size_t	size;
	char	*row;
	int		i;
	int		len;

	i = 0;
	len = get_map_size(game);
	while (++i < len - 1)
	{
		row = ft_strtrim(game->map[i], " \n\t");
		if (ft_strlen(row) == 0)
		{
			free(row);
			continue ;
		}
		size = ft_strlen(row) - 1;
		if (row[size] != '1')
		{
			free(row);
			return (perr("right border is not surrounded by walls"));
		}
		free(row);
	}
	return (1);
}

static int	is_valid_bottom(t_game *game)
{
	int	j;
	int	len;

	j = -1;
	len = get_map_size(game);
	while (game->map[len - 1][++j])
	{
		if (game->map[len - 1][j] == ' ')
			continue ;
		if (game->map[len - 1][j] != '1')
			return (perr("bottom border is not surrounded by walls"));
	}
	return (1);
}

int	validate_sides(t_game *game)
{
	if (!is_valid_top(game))
		return (0);
	if (!is_valid_left(game))
		return (0);
	if (!is_valid_right(game))
		return (0);
	if (!is_valid_bottom(game))
		return (0);
	return (1);
}
