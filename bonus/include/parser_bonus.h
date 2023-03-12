/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:56:04 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:37:19 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "cub3d_bonus.h"

int		init_map(t_game *game, char **av);
int		validate_map_attributes(char **map);
int		validate_map(t_game *game, char *filepath);

#endif
