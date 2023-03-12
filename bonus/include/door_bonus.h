/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:58:18 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:37:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_BONUS_H
# define DOOR_BONUS_H

# include "cub3d_bonus.h"

// door
int		is_valid_attributes_with_door(char **map);
int		validate_identifiers_with_door(char *filepath);
void	open_door_and_update_matrix(t_game *game);
int		check_door_texture(t_game *game, char *row);
char	*get_map_with_door(int fd, int *map_width, int *map_height);
int		init_config_params_with_door(t_game *game, char *filepath);
void	close_door_and_update_matrix(t_game *game);

// sprites
int		check_animated_texture(t_game *game, char *row);

#endif
