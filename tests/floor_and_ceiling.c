#include "cub3d.h"
#include "debug.h"
#include "parser.h"
#include <criterion/criterion.h>

Test(floor_and_ceiling, open)
{
	t_game game;
	t_argb color;

	game.floor_color = separate_argb_color(0x00FFFF);
	game.ceilling_color = separate_argb_color(0xFF00FF);
	game.map = calloc(11, sizeof(char *));
	game.map[0] = strdup("1111111111");
	game.map[1] = strdup("1000000001");
	game.map[2] = strdup("1000000001");
	game.map[3] = strdup("1000000001");
	game.map[4] = strdup("1000000001");
	game.map[5] = strdup("1000000001");
	game.map[6] = strdup("1000000001");
	game.map[7] = strdup("1000000001");
	game.map[8] = strdup("1000N00001");
	game.map[9] = strdup("1111111111");
	game_setup(&game);
	game.player.pos = create_vector(5, 8);
	reset_canvas(game.frame_3d);
	color = mlx_get_argb_image_pixel(game.frame_3d, 0, 0);
	cr_assert_eq(game.ceilling_color.argb, color.argb);
	color = mlx_get_argb_image_pixel(game.frame_3d, 0, game.frame_3d->height - 1);
	cr_assert_eq(game.floor_color.argb, color.argb);
	destroy_game(&game);
}
