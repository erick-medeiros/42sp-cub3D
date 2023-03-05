/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:56:04 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/05 18:15:21 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

int		init_map(t_game *game, char **av);
int		validate_map_attributes(char **map);
int		is_row_empty(char **row, int fd);
int		validate_map(t_game *game, char *filepath);

#endif
