/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:39:18 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 12:47:51 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "config.h"

t_img	*get_sprite_texture(t_sprite *sprite)
{
	t_img	*texture;

	texture = sprite->textures[sprite->num_texture];
	if (!texture)
	{
		sprite->num_texture = 0;
		return (get_sprite_texture(sprite));
	}
	if (sprite->frames == FRAMES_PER_SPRITE)
	{
		sprite->num_texture++;
		sprite->frames = 0;
	}
	else
		sprite->frames++;
	return (texture);
}
