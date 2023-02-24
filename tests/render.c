#include "cub3d.h"
#include "debug.h"
#include "parser.h"
#include <criterion/criterion.h>

#define RUNFOLDER "./tests/"

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
	game.window_width = 2;
	game.window_height = 2;
	game_setup(&game);
	reset_canvas(game.frame_3d);
	color = mlx_get_argb_image_pixel(game.frame_3d, 0, 0);
	cr_assert_eq(color.argb, ceilling);
	color = mlx_get_argb_image_pixel(game.frame_3d, 0, game.frame_3d->height - 1);
	cr_assert_eq(color.argb, floor);
	destroy_game(&game);
}

Test(render, textures)
{
	const char *north_texture = RUNFOLDER "assets/cyan.xpm";
	const char *south_texture = RUNFOLDER "assets/green.xpm";
	const char *west_texture = RUNFOLDER "assets/magenta.xpm";
	const char *east_texture = RUNFOLDER "assets/yellow.xpm";
	t_game      game;
	t_argb      color;

	game_init(&game);
	game.window_width = 1;
	game.window_height = 1;
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, (char *) north_texture);
	color = mlx_get_argb_image_pixel(game.north_texture, 0, 0);
	cr_assert_eq(color.argb, 0x00FFFF);
	game.south_texture = create_canvas_texture(game.mlx, (char *) south_texture);
	color = mlx_get_argb_image_pixel(game.south_texture, 0, 0);
	cr_assert_eq(color.argb, 0x00FF00);
	game.west_texture = create_canvas_texture(game.mlx, (char *) west_texture);
	color = mlx_get_argb_image_pixel(game.west_texture, 0, 0);
	cr_assert_eq(color.argb, 0xFF00FF);
	game.east_texture = create_canvas_texture(game.mlx, (char *) east_texture);
	color = mlx_get_argb_image_pixel(game.east_texture, 0, 0);
	cr_assert_eq(color.argb, 0xFFFF00);
	destroy_game(&game);
}
