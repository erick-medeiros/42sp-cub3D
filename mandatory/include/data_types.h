/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:16:06 by eandre-f          #+#    #+#             */
/*   Updated: 2023/02/23 01:36:48 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# define XKEY_ESC 65307
# define XKEY_W 119
# define XKEY_A 97
# define XKEY_S 115
# define XKEY_D 100
# define XKEY_LEFT_ARROW 65361
# define XKEY_RIGHT_ARROW 65363

# define FOV_RAD 0.66
# define MOVEMENT_SPEED 0.04
# define STRAFE_SPEED 0.04
# define ROTATE_SPEED_RAD 0.04

# define MLX_ERROR 1

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

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

typedef struct s_control
{
	t_bool	walk_up;
	t_bool	walk_down;
	t_bool	strafe_left;
	t_bool	strafe_right;
	t_bool	rotate_left;
	t_bool	rotate_right;
}	t_control;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	movement;
	t_vector	strafe;
	double		rotate_speed;
	double		move_speed;
	double		strafe_speed;
}	t_player;

typedef struct s_minimap
{
	t_vector	pos;
	double		scale;
	t_img		*frame;
}	t_minimap;

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
	t_control	control;
	t_img		*frame_3d;
	t_player	player;
	t_minimap	minimap;
}	t_game;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

#endif
