/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:29 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	validate_map(t_game *game, char *filepath)
{
	if (!validate_map_lines(filepath))
		return (0);
	if (!validate_sides(game))
		return (0);
	if (!validate_inner(game))
		return (0);
	return (1);
}
