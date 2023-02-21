/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_octantes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:42:42 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/21 00:46:51 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"

void	bresenham_axis(t_bresenham *b, t_img *img, int color)
{
	b->xi = b->p1.x;
	b->yi = b->p1.y;
	if (b->delta_x == 0 && b->delta_y == 0)
		return ;
	while (b->delta_x > b->xi - b->p1.x || b->delta_y > b->yi - b->p1.y)
	{
		mlx_put_image_pixel(img, b->xi, b->yi, color);
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

void	bresenham_octante_1_5(t_bresenham *b, t_img *img, int color)
{
	b->xi = b->p1.x;
	b->yi = b->p1.y;
	b->error = (2 * b->delta_y) - b->delta_x;
	while (b->xi <= b->p2.x)
	{
		mlx_put_image_pixel(img, b->xi, b->yi, color);
		if (b->error <= 0)
			b->error += b->delta_y;
		else
		{
			b->error += (b->delta_y - b->delta_x);
			++b->yi;
		}
		++b->xi;
	}
}

void	bresenham_octante_8_4(t_bresenham *b, t_img *img, int color)
{
	b->xi = b->p1.x;
	b->yi = b->p1.y;
	b->error = (2 * b->delta_y) + b->delta_x;
	while (b->xi <= b->p2.x)
	{
		mlx_put_image_pixel(img, b->xi, b->yi, color);
		if (b->error >= 0)
			b->error += b->delta_y;
		else
		{
			b->error += (b->delta_y + b->delta_x);
			--b->yi;
		}
		++b->xi;
	}
}

void	bresenham_octante_2_6(t_bresenham *b, t_img *img, int color)
{
	b->xi = b->p1.x;
	b->yi = b->p1.y;
	b->error = (2 * b->delta_x) - b->delta_y;
	while (b->yi <= b->p2.y)
	{
		mlx_put_image_pixel(img, b->xi, b->yi, color);
		if (b->error <= 0)
			b->error += b->delta_x;
		else
		{
			b->error += (b->delta_x - b->delta_y);
			++b->xi;
		}
		++b->yi;
	}
}

void	bresenham_octante_7_3(t_bresenham *b, t_img *img, int color)
{
	b->xi = b->p1.x;
	b->yi = b->p1.y;
	b->error = (2 * b->delta_x) + b->delta_y;
	while (b->yi >= b->p2.y)
	{
		mlx_put_image_pixel(img, b->xi, b->yi, color);
		if (b->error <= 0)
			b->error += b->delta_x;
		else
		{
			b->error += (b->delta_x + b->delta_y);
			++b->xi;
		}
		--b->yi;
	}
}
