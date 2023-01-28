/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:31:20 by eandre-f          #+#    #+#             */
/*   Updated: 2023/01/28 10:31:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

int	mlx_keypress_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	const int	x_event = 2;
	const int	x_mask = 1L << 0;

	return (mlx_hook(win_ptr, x_event, x_mask, funct_ptr, param));
}

int	mlx_keyrelease_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	return (mlx_key_hook(win_ptr, funct_ptr, param));
}

int	mlx_destroynotify_hook(void *win_ptr, int (*funct_ptr)(), void *param)
{
	const int	x_event = 17;
	const int	x_mask = 0;

	return (mlx_hook(win_ptr, x_event, x_mask, funct_ptr, param));
}
