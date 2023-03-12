/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 22:56:07 by frosa-ma          #+#    #+#             */
/*   Updated: 2023/03/11 22:56:26 by frosa-ma         ###   ########.fr       */
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
