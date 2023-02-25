/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:15:23 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/25 13:02:29 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

typedef enum e_hit
{
	HIT_X,
	HIT_Y,
	HIT_NORTH,
	HIT_SOUTH,
	HIT_EAST,
	HIT_WEST
}	t_hit;

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
}	t_engine;

typedef struct s_ray_line
{
	int	start_y;
	int	end_y;
	int	hit_side;
}	t_ray_line;

void	raycaster_run_dda(t_game *game, t_engine *engine);
void	raycaster_draw_line(t_game *game, t_vector start, t_vector end,
			int hit_side);

void	raycaster_ceiling(t_img *img, int argb_color);
void	raycaster_floor(t_img *img, int argb_color);

// minimap
void	draw_player(t_game *game, t_minimap *minimap);
void	draw_minimap(t_game *game);
t_img	*raycaster_minimap(t_game *game);
void	draw_minimap_ray(t_game *game, t_engine *engine, t_vector ray_dir);

#endif
