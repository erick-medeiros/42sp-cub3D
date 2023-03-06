/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:15:45 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/06 11:18:37 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"
# include "raycaster.h"

# define MINIMAP_COLOR_GRID 0x000
# define MINIMAP_COLOR_FLOOR 0xFFFFFF
# define MINIMAP_COLOR_WALL 0xFAAFFF
# define MINIMAP_COLOR_PLAYER 0xFF0000
# define MINIMAP_COLOR_RAY 0x00FF00
# define MINIMAP_COLOR_TRANSPARENT 0xFF000000
# define MINIMAP_WINDOW_SCALE 0.15
# define MINIMAP_MAP_SCALE 15

void	init_minimap(t_game *game);
void	init_minimap_fullscreen(t_game *game);
void	destroy_minimap(void *mlx, t_minimap *minimap);

void	draw_map_2d(t_game *game, t_img *frame, double scale);
void	draw_minimap(t_game *game);
void	draw_fullscreen_minimap(t_game *game);
void	draw_minimap_ray(t_game *game, t_engine *engine);
void	draw_minimap_fullscreen_ray(t_game *game, t_engine *engine,
			double euclidian_dist);

#endif
