/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:15:23 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/02 12:19:47 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

# define HIT_X 1
# define HIT_Y 2

typedef struct e_engine
{
	t_vector	ray_dir;
	double		delta_dist_x;
	double		delta_dist_y;
	t_vector	map_pos;
	double		dist_to_side_x;
	double		dist_to_side_y;
	int			step_x;
	int			step_y;
	int			hit_side;
	t_vector	wall_hit;
	double		perp_wall_dist;
	double		dda_line_size_x;
	double		dda_line_size_y;
	int			line_height;
	int			line_start;
	int			line_end;
	double		wall_hit_x;
	t_img		*texture;
	t_argb		color;
}	t_engine;

void	raycaster_perform_dda(t_game *game, t_engine *engine);
void	raycaster_draw_line(t_game *game, t_engine *engine, int pixel);

// minimap
void	draw_player(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game);
t_img	*raycaster_minimap(t_game *game);
void	draw_minimap_ray(t_game *game, t_engine *engine, t_vector ray_dir);

#endif
