#include "cub3d.h"
#include "debug.h"
#include <criterion/criterion.h>

void create_map_10x10(t_game *game)
{
	game->map = calloc(11, sizeof(char *));
	game->map[0] = strdup("1111111111");
	game->map[1] = strdup("1000000001");
	game->map[2] = strdup("1000000001");
	game->map[3] = strdup("1000000001");
	game->map[4] = strdup("1000N00001");
	game->map[5] = strdup("1000000001");
	game->map[6] = strdup("1000000001");
	game->map[7] = strdup("1000000001");
	game->map[8] = strdup("1000000001");
	game->map[9] = strdup("1111111111");
	game->map_width = 10;
	game->map_height = 10;
}

Test(keyboard, init_false)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, w)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	handle_keypress(XKEY_W, &game);
	cr_assert(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
	handle_keyrelease(XKEY_W, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, a)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	handle_keypress(XKEY_A, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
	handle_keyrelease(XKEY_A, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, s)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	handle_keypress(XKEY_S, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
	handle_keyrelease(XKEY_S, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, d)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	handle_keypress(XKEY_D, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
	handle_keyrelease(XKEY_D, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, left_arrow)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	handle_keypress(XKEY_LEFT_ARROW, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
	handle_keyrelease(XKEY_LEFT_ARROW, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, right_arrow)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	handle_keypress(XKEY_RIGHT_ARROW, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert(game.control.rotate_right);
	handle_keyrelease(XKEY_RIGHT_ARROW, &game);
	cr_assert_not(game.control.walk_up);
	cr_assert_not(game.control.walk_down);
	cr_assert_not(game.control.strafe_left);
	cr_assert_not(game.control.strafe_right);
	cr_assert_not(game.control.rotate_left);
	cr_assert_not(game.control.rotate_right);
}

Test(keyboard, walk_up)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.config.mouse = FALSE;
	create_map_10x10(&game);
	game.player.pos = create_vector(5, 5);
	player_orientation(&game.player, 'N');
	game.player.move_speed = 2;
	game.control.walk_up = TRUE;
	update_input(&game, &game.player);
	cr_assert_eq(game.player.pos.x, 5);
	cr_assert_eq(game.player.pos.y, 3);
	destroy_game(&game);
}

Test(keyboard, walk_down)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.config.mouse = FALSE;
	create_map_10x10(&game);
	game.player.pos = create_vector(5, 5);
	player_orientation(&game.player, 'N');
	game.player.move_speed = -2;
	update_input(&game, &game.player);
	cr_assert_eq(game.player.pos.x, 5);
	cr_assert_eq(game.player.pos.y, 7);
	destroy_game(&game);
}

Test(keyboard, strafe_left)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.config.mouse = FALSE;
	create_map_10x10(&game);
	game.player.pos = create_vector(5, 5);
	player_orientation(&game.player, 'N');
	game.player.strafe_speed = -2;
	update_input(&game, &game.player);
	cr_assert_eq(game.player.pos.x, 3);
	cr_assert_eq(game.player.pos.y, 5);
	destroy_game(&game);
}

Test(keyboard, strafe_right)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.config.mouse = FALSE;
	create_map_10x10(&game);
	game.player.pos = create_vector(5, 5);
	player_orientation(&game.player, 'N');
	game.player.strafe_speed = 2;
	update_input(&game, &game.player);
	cr_assert_eq(game.player.pos.x, 7);
	cr_assert_eq(game.player.pos.y, 5);
	destroy_game(&game);
}

Test(keyboard, rotate_left)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.config.mouse = FALSE;
	create_map_10x10(&game);
	game.player.pos = create_vector(5, 5);
	game.player.dir = create_vector(0, 1);
	game.player.rotate_speed = -M_PI_2;
	update_input(&game, &game.player);
	cr_assert_float_eq(game.player.dir.x, 1.000000, 1e-6);
	cr_assert_float_eq(game.player.dir.y, 0.000000, 1e-6);
	destroy_game(&game);
}

Test(keyboard, rotate_right)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.config.mouse = FALSE;
	create_map_10x10(&game);
	game.player.pos = create_vector(5, 5);
	game.player.dir = create_vector(0, 1);
	game.player.rotate_speed = M_PI_2;
	update_input(&game, &game.player);
	cr_assert_float_eq(game.player.dir.x, -1.000000, 1e-6);
	cr_assert_float_eq(game.player.dir.y, 0.000000, 1e-6);
	destroy_game(&game);
}
