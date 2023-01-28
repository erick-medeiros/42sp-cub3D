/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:50:28 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/28 10:50:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx_extra.h" // lib: minilibx extra
# include <fcntl.h>     // open
# include <libft.h>     // lib: libft
# include <math.h>      // lib: math
# include <mlx.h>       // lib: minilibx
# include <stdio.h>     // printf, perror
# include <stdlib.h>    // malloc, free, exit
# include <string.h>    // strerror
# include <unistd.h>    // close, read, write

typedef struct s_game
{
	void	*mlx;
	void	*win;
}	t_game;

int	handle_keypress(int keycode, t_game *game);
int	handle_keyrelease(int keycode, t_game *game);

#endif
