/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:19:13 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	count_char_in_map(t_game *game, char c)
{
	t_px	px;
	int		i;

	i = 0;
	px.y = -1;
	while (++px.y < game->map_height)
	{
		px.x = -1;
		while (++px.x < game->map_width)
			if (game->map[px.y][px.x] == c)
				i++;
	}
	return (i);
}
