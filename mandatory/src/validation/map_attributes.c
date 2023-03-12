/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:12:39 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 18:13:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "door.h"

static int	is_valid_attributes(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!is_reserved_ch(map[i][j], "01 NSEWFC\t\n"))
				return (0);
		}
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

int	validate_map_attributes(char **map)
{
	if (!is_player_found(map))
		return (perr("invalid number of players"));
	if (!is_valid_attributes(map))
		return (perr("invalid map attribute"));
	return (1);
}
