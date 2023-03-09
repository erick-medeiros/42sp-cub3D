#include "cub3d.h"
#include "debug.h"
#include "parser.h"
#include <criterion/criterion.h>

#define RUNFOLDER "./"

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
	reset_canvas(game.canvas);
	color = mlx_get_argb_image_pixel(game.canvas, 0, 0);
	cr_assert_eq(color.argb, ceilling);
	color = mlx_get_argb_image_pixel(game.canvas, 0, game.canvas->height - 1);
	cr_assert_eq(color.argb, floor);
	destroy_game(&game);
}

Test(render, load_textures)
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

Test(render, render_textures)
{
	const char  *north_texture = RUNFOLDER "assets/red.xpm";
	const char  *south_texture = RUNFOLDER "assets/green.xpm";
	const char  *west_texture = RUNFOLDER "assets/blue.xpm";
	const char  *east_texture = RUNFOLDER "assets/yellow.xpm";
	const t_argb ceilling = separate_argb_color(0x00FFFF);
	const t_argb floor = separate_argb_color(0xFF00FF);
	t_game       game;
	t_argb       color;

	game_init(&game);
	game.window_width = 10;
	game.window_height = 10;
	game.map = calloc(4, sizeof(char *));
	game.map[0] = strdup("111");
	game.map[1] = strdup("1N1");
	game.map[2] = strdup("111");
	game.map_width = 3;
	game.map_height = 3;
	game.ceilling_color = ceilling;
	game.floor_color = floor;
	game_setup(&game);
	game.north_texture = create_canvas_texture(game.mlx, (char *) north_texture);
	game.south_texture = create_canvas_texture(game.mlx, (char *) south_texture);
	game.west_texture = create_canvas_texture(game.mlx, (char *) west_texture);
	game.east_texture = create_canvas_texture(game.mlx, (char *) east_texture);
	game.player.pos = create_vector(1.5, 1.5);
	// north
	game.player.dir = create_vector(0, -1);
	render(&game);
	color = mlx_get_argb_image_pixel(game.canvas, game.window_width / 2, game.window_height / 2);
	cr_assert_eq(color.argb, 0xFF0000);
	// south
	game.player.dir = create_vector(0, 1);
	render(&game);
	color = mlx_get_argb_image_pixel(game.canvas, game.window_width / 2, game.window_height / 2);
	cr_assert_eq(color.argb, 0x00FF00);
	// east
	game.player.dir = create_vector(1, 0);
	render(&game);
	color = mlx_get_argb_image_pixel(game.canvas, game.window_width / 2, game.window_height / 2);
	cr_assert_eq(color.argb, 0xFFFF00);
	// west
	game.player.dir = create_vector(-1, 0);
	render(&game);
	color = mlx_get_argb_image_pixel(game.canvas, game.window_width / 2, game.window_height / 2);
	cr_assert_eq(color.argb, 0x0000FF);
	destroy_game(&game);
}
