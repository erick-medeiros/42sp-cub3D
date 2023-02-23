#include "cub3d.h"
#include <criterion/criterion.h>

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
	game.player.pos = create_vector(10, 10);
	game.player.dir = create_vector(0, 1);
	game.player.move_speed = 2;
	game.control.walk_up = TRUE;
	input_handler(&game.player, &game.control);
	update_input(&game.player);
	cr_assert_eq(game.player.pos.x, 10);
	cr_assert_eq(game.player.pos.y, 12);
}

Test(keyboard, walk_down)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.player.pos = create_vector(10, 10);
	game.player.dir = create_vector(0, 1);
	game.player.move_speed = 2;
	game.control.walk_down = TRUE;
	input_handler(&game.player, &game.control);
	update_input(&game.player);
	cr_assert_eq(game.player.pos.x, 10);
	cr_assert_eq(game.player.pos.y, 8);
}

Test(keyboard, strafe_left)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.player.pos = create_vector(10, 10);
	game.player.dir = create_vector(0, 1);
	game.player.strafe_speed = 2;
	game.control.strafe_left = TRUE;
	input_handler(&game.player, &game.control);
	update_input(&game.player);
	cr_assert_eq(game.player.pos.x, 12);
	cr_assert_eq(game.player.pos.y, 10);
}

Test(keyboard, strafe_right)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.player.pos = create_vector(10, 10);
	game.player.dir = create_vector(0, 1);
	game.player.strafe_speed = 2;
	game.control.strafe_right = TRUE;
	input_handler(&game.player, &game.control);
	update_input(&game.player);
	cr_assert_eq(game.player.pos.x, 8);
	cr_assert_eq(game.player.pos.y, 10);
}

Test(keyboard, rotate_left)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.player.pos = create_vector(10, 10);
	game.player.dir = create_vector(0, 1);
	game.player.rotate_speed = -M_PI_2;
	update_input(&game.player);
	cr_assert_float_eq(game.player.dir.x, 1.000000, 1e-6);
	cr_assert_float_eq(game.player.dir.y, 0.000000, 1e-6);
}

Test(keyboard, rotate_right)
{
	t_game game;

	game.map = NULL;
	game_init(&game);
	game.player.pos = create_vector(10, 10);
	game.player.dir = create_vector(0, 1);
	game.player.rotate_speed = M_PI_2;
	update_input(&game.player);
	cr_assert_float_eq(game.player.dir.x, -1.000000, 1e-6);
	cr_assert_float_eq(game.player.dir.y, 0.000000, 1e-6);
}
