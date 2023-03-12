/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:15:23 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 18:43:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_BONUS_H
# define RAYCASTER_BONUS_H

# include "cub3d_bonus.h"

# define HIT_X 1
# define HIT_Y 2

typedef struct s_engine
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
	t_img		*frame;
	t_img		*texture;
	t_argb		color;
}	t_engine;

typedef struct s_sprite_casting
{
	t_vector	transform;
	t_px		draw_start;
	t_px		draw_end;
	t_rect		dimension;
	t_img		*texture;
}	t_sprite_casting;

void		update_input(t_game *game, t_player *player);
t_vector	check_collision(t_game *game, t_vector pos, t_vector new_pos,
				t_vector movement);
void		raycaster_perform_dda(t_game *game, t_engine *engine);
void		raycaster_draw_line(t_game *game, t_engine *engine, int pixel);

t_img		*get_sprite_texture(t_sprite *sprite);
void		raycaster_sprites(t_game *game, t_engine *engine);

// bonus
void		raycaster_get_texture_door(t_game *game, t_engine *engine);

#endif
