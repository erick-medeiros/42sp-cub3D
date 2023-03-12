/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:42:29 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/12 17:32:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	set_mag_vector(t_vector v, double new_mag)
{
	double	mag;

	mag = mag_vector(v);
	v.x = v.x * new_mag / mag;
	v.y = v.y * new_mag / mag;
	return (v);
}
