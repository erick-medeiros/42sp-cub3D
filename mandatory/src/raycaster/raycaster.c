/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 11:30:12 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 15:20:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"
#include "cub3d.h"
#include "debug.h"
#include "feature_flags.h"
#include "minimap.h"

void	update_input(t_game *game, t_player *player)
{
	t_vector	movement;
	t_vector	new_pos;
	t_vector	collision;

	if (player->rotate_speed)
	{
		player->dir = rotate_vector(player->dir, player->rotate_speed);
		player->plane = rotate_vector(player->plane, player->rotate_speed);
	}
	movement = create_vector(0, 0);
	if (player->move_speed)
		movement = add_vector(movement,
				mult_vector_scalar(player->dir, player->move_speed));
	if (player->strafe_speed)
		movement = add_vector(movement,
				mult_vector_scalar(rotate_vector(player->dir, M_PI_2),
					player->strafe_speed));
	new_pos = add_vector(game->player.pos, movement);
	if (FEATURE_FLAG_COLLISION)
		collision = check_collision(game, game->player.pos, new_pos, movement);
	else
		collision = check_space_collision(game, new_pos);
	movement = mult_vector_vector(movement, collision);
	game->player.pos = add_vector(game->player.pos, movement);
}

static t_vector	raycaster_ray_dir(t_img *img, t_player player, int pixel)
{
	double		mult;
	t_vector	camera_pixel;
	t_vector	ray_dir;

	mult = 2 * ((double)pixel / img->width) - 1;
	camera_pixel = mult_vector_scalar(player.plane, mult);
	ray_dir = add_vector(player.dir, camera_pixel);
	return (ray_dir);
}

void	raycaster_sprites(t_game *game, t_engine *engine)
{
	double spriteX = game->sprite.pos.x - game->player.pos.x;
    double spriteY = game->sprite.pos.y - game->player.pos.y;
	double invDet = 1.0 / (game->player.plane.x * game->player.dir.y - game->player.dir.x * game->player.plane.y);
	double transformX = invDet * (game->player.dir.y * spriteX - game->player.dir.x * spriteY); 
    double transformY = invDet * (-game->player.plane.y * spriteX + game->player.plane.x * spriteY);
	int spriteScreenX = ((double)engine->frame->width / 2) * (1 + transformX / transformY);
	int spriteHeight = fabs((double)engine->frame->height / (transformY));
	int drawStartY = -spriteHeight / 2 + engine->frame->height / 2; 
    if(drawStartY < 0) drawStartY = 0; 
    int drawEndY = spriteHeight / 2 + engine->frame->height / 2; 
    if(drawEndY >= engine->frame->height) drawEndY = engine->frame->height - 1;
    int spriteWidth = fabs((engine->frame->height / (transformY))); 
    int drawStartX = -spriteWidth / 2 + spriteScreenX; 
    if(drawStartX < 0) drawStartX = 0; 
    int drawEndX = spriteWidth / 2 + spriteScreenX; 
    if(drawEndX >= engine->frame->width) drawEndX = engine->frame->width - 1;
	t_img *texture = get_sprite_texture(&game->sprite);
	for(int stripe = drawStartX; stripe < drawEndX; stripe++) 
      {
        int texX = (256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texture->width / spriteWidth) / 256;
         if(transformY > 0 && stripe > 0 && stripe < engine->frame->width && transformY < game->all_perpend[stripe]) 
        for(int y = drawStartY; y < drawEndY; y++)
         {
          int d = (y) * 256 - engine->frame->height * 128 + spriteHeight * 128;
           int texY = ((d * texture->height) / spriteHeight) / 256; 
		   mlx_copy_image_pixel(engine->frame, (t_px){stripe, y}, texture, (t_px){texX, texY});
         } 
      } 
}

void	raycaster(t_game *game, t_img *img)
{
	t_engine	engine;
	int			pixel;

	update_input(game, &game->player);
	if (FEATURE_FLAG_MINIMAP && game->minimap.frame)
		draw_minimap(game);
	engine.frame = img;
	pixel = 0;
	while (pixel < img->width)
	{
		engine.ray_dir = raycaster_ray_dir(engine.frame, game->player, pixel);
		raycaster_perform_dda(game, &engine);
		game->all_perpend[pixel] = engine.perp_wall_dist;
		raycaster_draw_line(game, &engine, pixel);
		if (FEATURE_FLAG_MINIMAP && game->minimap.frame)
			draw_minimap_ray(game, &engine);
		pixel++;
	}
	raycaster_sprites(game, &engine);
}
