#include "cub3d.h"
#include "debug.h"
#include "parser.h"
#include <criterion/criterion.h>

Test(render, floor_and_ceiling)
{
	int    floor;
	int    ceilling;
	t_game game;
	t_argb color;

	floor = 0x00FFFF;
	ceilling = 0xFF00FF;
	game_init(&game);
	game.floor_color = separate_argb_color(floor);
	game.ceilling_color = separate_argb_color(ceilling);
	game_setup(&game);
	reset_canvas(game.frame_3d);
	color = mlx_get_argb_image_pixel(game.frame_3d, 0, 0);
	cr_assert_eq(color.argb, ceilling);
	color = mlx_get_argb_image_pixel(game.frame_3d, 0, game.frame_3d->height - 1);
	cr_assert_eq(color.argb, floor);
	destroy_game(&game);
}
