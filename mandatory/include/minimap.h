/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:15:45 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/03 10:39:41 by eandre-f         ###   ########.fr       */
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

void	init_minimap(t_game *game);
void	draw_player(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game);
t_img	*raycaster_minimap(t_game *game);
void	draw_minimap_ray(t_game *game, t_engine *engine, t_vector ray_dir);

#endif
