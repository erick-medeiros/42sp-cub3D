/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:24:08 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/10 15:45:50 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	calculate_scale(t_game *game)
{
	int	scale;

	scale = game->canvas->width / game->map_width;
	if (scale > game->canvas->height / game->map_height)
		scale = game->canvas->height / game->map_height;
	return (scale);
}

static t_rect	create_rectangle(int i, int j, int scale)
{
	t_rect	rect;

	rect.x = j * scale;
	rect.y = i * scale;
	rect.width = scale;
	rect.height = scale;
	return (rect);
}

static int	get_color(char c)
{
	if (c == '\0')
		return (0xFFF00F);
	else if (c == ' ')
		return (0x00FFFF);
	else if (c == '1')
		return (0xFF00FF);
	else if (c == '0')
		return (0xFFFFFF);
	else
		return (0xFF0000);
}

void	render_map(t_game *game)
{
	int		scale;
	int		i;
	int		j;

	draw_background(game->canvas, 0x000000);
	scale = calculate_scale(game);
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (!game->map[i][j])
				break ;
			draw_rectangle(game->canvas,
				create_rectangle(i, j, scale), get_color(game->map[i][j]));
		}
		--j;
		while (++j < game->map_width)
			draw_rectangle(game->canvas,
				create_rectangle(i, j, scale), get_color('\0'));
	}
}
