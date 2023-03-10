/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:01:24 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 19:02:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	mag_vector(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

t_vector	normalize_vector(t_vector v1)
{
	t_vector	v;
	double		mag;

	v = create_vector(0, 0);
	mag = mag_vector(v1);
	if (mag != 0)
		v = mult_vector_scalar(v1, 1 / mag);
	return (v);
}

double	dot_product_of_vector(t_vector v1, t_vector v2)
{
	v1 = normalize_vector(v1);
	v2 = normalize_vector(v2);
	return (v1.x * v2.x + v1.y + v2.y);
}

// return in radian

double	angle_between_vectors(t_vector v1, t_vector v2)
{
	double	cos;

	cos = dot_product_of_vector(v1, v2) / (mag_vector(v1) * mag_vector(v2));
	return (acos(cos));
}

t_vector	rotate_vector(t_vector v, double angle_radian)
{
	t_vector	new;

	new.x = v.x * cos(angle_radian) - v.y * sin(angle_radian);
	new.y = v.x * sin(angle_radian) + v.y * cos(angle_radian);
	return (new);
}
