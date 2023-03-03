/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:56:04 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/02 19:37:32 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

int		init_map(t_game *game, char **av);

int		is_valid_map_attribute(char **map);
int		is_player_found(char **map);
int		is_valid_map(char **map);
int		is_row_empty(char **row, int fd);

#endif
