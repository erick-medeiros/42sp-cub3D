/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:16:06 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/17 18:45:37 by eandre-f         ###   ########.fr       */
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

// HINT: we will probably need something like this
typedef struct s_params
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		ceil;
	int		floor;
}	t_params;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		*canvas;
	t_img		*north_texture;
	t_img		*south_texture;
	t_img		*west_texture;
	t_img		*east_texture;
	t_argb		floor_color;
	t_argb		ceilling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_img		*_minimap;
	t_img		*_engine;
	t_vector	pos;
	t_vector	dir;
}	t_game;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

#endif
