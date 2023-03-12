/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:56:07 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 00:22:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_animated_texture(t_game *game, char *row)
{
	char	**tokens;
	int		i;
	int		j;

	tokens = get_matrix(row);
	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
		i++;
	game->sprites.textures = ft_calloc(sizeof(char *), i);
	i = 0;
	j = -1;
	while (tokens[++i])
		game->sprites.textures[++j] = ft_strtrim(tokens[i], " \n\t");
	ft_free_matrix(tokens);
	return (1);
}

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

void	load_sprite(t_game *game, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (game->sprites.textures[i])
		i++;
	sprite->textures = ft_calloc(i + 1, sizeof(t_img *));
	i = 0;
	while (game->sprites.textures[i])
	{
		sprite->textures[i] = create_canvas_texture(game->mlx,
				game->sprites.textures[i]);
		i++;
	}
	sprite->num_texture = 0;
	sprite->frames = 0;
	sprite->pos = create_vector(0, 0);
}

void	init_animation(t_game *game)
{
	t_px	px;
	int		i;

	i = count_char_in_map(game, 'A');
	game->animation.total_sprites = i;
	game->animation.sprites = ft_calloc(i + 1, sizeof(t_sprite));
	game->animation.sprite_order = ft_calloc(i + 1, sizeof(int));
	game->animation.sprite_distance = ft_calloc(i + 1, sizeof(int));
	i = 0;
	px.y = -1;
	while (++px.y < game->map_height)
	{
		px.x = -1;
		while (++px.x < game->map_width)
		{
			if (game->map[px.y][px.x] == 'A')
			{
				load_sprite(game, &(game->animation.sprites[i]));
				game->animation.sprites[i].pos = add_vector(
						create_vector(px.x, px.y), create_vector(0.5, 0.5));
				i++;
			}
		}
	}
}

void	destroy_animation(void *mlx, t_sprite *sprites, t_animation *animation)
{
	int	i;

	i = 0;
	while (sprites && sprites[i].textures)
	{
		sprites[i].num_texture = 0;
		while (sprites[i].textures
			&& sprites[i].textures[sprites[i].num_texture])
		{
			sprites[i].textures[sprites[i].num_texture] = destroy_canvas(mlx,
					sprites[i].textures[sprites[i].num_texture]);
			sprites[i].num_texture++;
		}
		free(sprites[i].textures);
		i++;
	}
	free(sprites);
	free(animation->sprite_order);
	free(animation->sprite_distance);
}
