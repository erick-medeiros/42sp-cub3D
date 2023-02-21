/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:06:27 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 13:11:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_vector(char *name, t_vector vector)
{
	if (name)
		printf("%s ", name);
	printf("x %lf y %lf\n", vector.x, vector.y);
}
