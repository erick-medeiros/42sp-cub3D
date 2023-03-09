#include "cub3d.h"
#include "raycaster.h"
#include <criterion/criterion.h>

Test(mouse_bonus, mouse)
{
	t_game   game;
	t_vector dir;
	t_px     fake_mouse;

	game_init(&game);
	game.window_width = 10;
	game.window_height = 10;
	game_setup(&game);
	game.map = calloc(4, sizeof(char *));
	game.map[0] = strdup("111");
	game.map[1] = strdup("1N1");
	game.map[2] = strdup("111");
	game.map_width = 3;
	game.map_height = 3;
	game.player.pos = create_vector(1.5, 1.5);
	// rotate right
	player_orientation(&game.player, 'N');
	dir = game.player.dir;
	fake_mouse.x = (game.canvas->width / 2) + 1;
	fake_mouse.y = game.canvas->height / 2;
	handle_mouse(fake_mouse.x, fake_mouse.y, &game);
	input_handler(&game);
	update_input(&game, &game.player);
	cr_assert(dir.x < game.player.dir.x);
	// rotate left
	player_orientation(&game.player, 'N');
	dir = game.player.dir;
	fake_mouse.x = (game.canvas->width / 2) - 1;
	fake_mouse.y = game.canvas->height / 2;
	handle_mouse(fake_mouse.x, fake_mouse.y, &game);
	input_handler(&game);
	update_input(&game, &game.player);
	cr_assert(dir.x > game.player.dir.x);
	//
	destroy_game(&game);
}