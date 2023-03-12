/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:16:06 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/11 22:45:13 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# include "stddef.h"

# define XKEY_ESC 65307
# define XKEY_W 119
# define XKEY_A 97
# define XKEY_S 115
# define XKEY_D 100
# define XKEY_LEFT_ARROW 65361
# define XKEY_RIGHT_ARROW 65363
# define XKEY_M 109
# define XKEY_SPACE 32

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
	int		bytes_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	size_t	size;
	void	*background;
	int		alpha_mask;
}	t_img;

typedef struct s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
	int	argb;
}	t_argb;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_px
{
	int	x;
	int	y;
}	t_px;

typedef struct s_control
{
	t_bool	walk_up;
	t_bool	walk_down;
	t_bool	strafe_left;
	t_bool	strafe_right;
	t_bool	rotate_left;
	t_bool	rotate_right;
	t_px	mouse;
	double	fov_ratio;
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
	t_px		pos;
	int			scale;
	t_img		*frame;
	t_img		*map_2d;
	t_img		*frame_fullscreen;
	double		edge_distance;
	t_px		pos_fullscreen;
	t_px		middle_frame;
	t_bool		fullscreen;
	double		scale_full;
}	t_minimap;

typedef struct s_colors
{
	char	*r;
	char	*g;
	char	*b;
}	t_colors;

typedef struct s_params
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	t_argb		ceilling_color;
	t_argb		floor_color;
	t_colors	floor;
	t_colors	ceil;
	char		*door_texture;
}	t_params;

typedef struct s_config
{
	t_bool	mouse;
}	t_config;

typedef struct s_sprites
{
	char	**textures;
}	t_sprites;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			window_width;
	int			window_height;
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
	t_player	player;
	t_minimap	minimap;
	t_params	params;
	t_config	config;
	int			is_door;
	int			door_range;
	t_img		*door_texture;
	t_sprites	sprites;
}	t_game;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
}	t_rect;

#endif
