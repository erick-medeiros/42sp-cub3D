/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framerate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:13:06 by eandre-f          #+#    #+#             */
/*   Updated: 2023/03/01 15:38:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <time.h> // forbidden

void	fps_meter(void *mlx, int max_frame)
{
	static int		frames = 0;
	static clock_t	start = 0;
	clock_t			end;
	double			time;
	static double	count = 0;

	if (frames == 0)
		start = clock();
	frames++;
	count++;
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	if (time >= 1.0)
	{
		printf("FPS: %.2f\n", count / time);
		count = 0;
		start = end;
	}
	if (frames == max_frame)
	{
		printf("MAX FRAME: %d\n", frames);
		mlx_loop_end(mlx);
	}
}
