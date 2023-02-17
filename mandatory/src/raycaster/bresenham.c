/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:24:27 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 14:01:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"

void	bresenham_axis(t_bresenham *b)
{
	if (b->delta_x == 0 && b->delta_y == 0)
		return ;
	while (b->delta_x > b->xi - b->p1.x || b->delta_y > b->yi - b->p1.y)
	{
		mlx_put_image_pixel(b->img, b->xi, b->yi, b->color);
		if (b->delta_x > 0)
			b->xi++;
		else if (b->delta_x < 0)
			b->xi--;
		if (b->delta_y > 0)
			b->yi++;
		else if (b->delta_y < 0)
			b->yi--;
	}
}

void	bresenham(t_img *img, t_point *p1, t_point *p2, int color)
{
	t_bresenham	b;

	p1->x = (int)p1->x;
	p1->y = (int)p1->y;
	p2->x = (int)p2->x;
	p2->y = (int)p2->y;
	b.p1 = *p1;
	b.p2 = *p2;
	if (p1->x > p2->x || (p1->x == p2->x && p1->y > p2->y))
	{
		b.p1 = *p2;
		b.p2 = *p1;
	}
	b.xi = b.p1.x;
	b.yi = b.p1.y;
	b.delta_x = b.p2.x - b.p1.x;
	b.delta_y = b.p2.y - b.p1.y;
	b.color = color;
	b.img = img;
	if (b.delta_x == 0 || b.delta_y == 0 || abs(b.delta_x) == abs(b.delta_y))
		bresenham_axis(&b);
	else
		bresenham_octantes(&b);
}
