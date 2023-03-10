/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:09:30 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:13:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "raycaster.h"
#include "debug.h"

int	render(t_game *game)
{
	input_handler(game);
	reset_canvas(game->canvas);
	raycaster(game, game->canvas);
	mlx_put_image_to_window(game->mlx, game->win, game->canvas->ptr, 0, 0);
	fps_meter(game->mlx, -1);
	return (0);
}
