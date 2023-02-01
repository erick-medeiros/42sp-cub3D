/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:16:06 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/01 19:27:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# define MLX_ERROR 1

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
	int	argb;
}	t_argb;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	*canvas;
}	t_game;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

#endif
