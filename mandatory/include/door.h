/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 03:58:18 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 04:28:22 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include "cub3d.h"

int		is_valid_attributes_with_door(char **map);
int		validate_identifiers_with_door(char *filepath);
void	open_door_and_update_matrix(t_game *game);

#endif
