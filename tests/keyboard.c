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
