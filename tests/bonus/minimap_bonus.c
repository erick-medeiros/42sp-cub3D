#include "minimap_bonus.h"
#include "cub3d_bonus.h"
#include <criterion/criterion.h>

Test(minimap_bonus, screen_size)
{
	t_game game;

	game_init(&game);
	game.window_width = 10;
	game.window_height = 10;
	game.map = calloc(4, sizeof(char *));
	game.map[0] = strdup("111");
	game.map[1] = strdup("1N1");
	game.map[2] = strdup("111");
	game.map_width = 3;
	game.map_height = 3;
	game_setup(&game);
	cr_assert(game.minimap.frame->width < game.canvas->width);
	cr_assert(game.minimap.frame->height < game.canvas->height);
	destroy_game(&game);
}

Test(minimap_bonus, fullscreen_size)
{
	t_game game;

	game_init(&game);
	game.window_width = 10;
	game.window_height = 10;
	game.map = calloc(4, sizeof(char *));
	game.map[0] = strdup("111");
	game.map[1] = strdup("1N1");
	game.map[2] = strdup("111");
	game.map_width = 3;
	game.map_height = 3;
	game_setup(&game);
	cr_assert(game.minimap.frame_fullscreen->width < game.canvas->width);
	cr_assert(game.minimap.frame_fullscreen->height < game.canvas->height);
	cr_assert(game.minimap.pos_fullscreen.x ==
	          (int) (((double) game.canvas->width / 2) -
	                 ((double) game.minimap.frame_fullscreen->width / 2)));
	cr_assert(game.minimap.pos_fullscreen.y ==
	          (int) (((double) game.canvas->height / 2) -
	                 ((double) game.minimap.frame_fullscreen->height / 2)));
	destroy_game(&game);
}
