/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 17:46:42 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/06 12:54:23 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_vertical_inner(t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = get_map_size(game);
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
					return (perr("invalid border"));
			}
			else if (is_reserved_ch(game->map[i][j], "0NSWE"))
				if (game->map[i][j + 1] == ' ')
					return (perr("invalid border"));
		}
	}
	return (1);
}

static int	validate_horizontal_inner(t_game *game)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = get_map_size(game);
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
					return (perr("invalid border"));
			}
			else if (is_reserved_ch(game->map[i][j], "0NSWE"))
				if (game->map[i + 1][j] == ' ')
					return (perr("invalid border"));
		}
	}
	return (1);
}

int	validate_inner(t_game *game)
{
	if (!validate_horizontal_inner(game))
		return (0);
	if (!validate_vertical_inner(game))
		return (0);
	return (1);
}
