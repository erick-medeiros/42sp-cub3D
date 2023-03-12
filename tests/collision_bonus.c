#include "cub3d_bonus.h"
#include "debug_bonus.h"
#include <criterion/criterion.h>

void create_map_4x4(t_game *game)
{
	game->map = calloc(4, sizeof(char *));
	game->map[0] = strdup("1111");
	game->map[1] = strdup("1001");
	game->map[2] = strdup("1001");
	game->map[3] = strdup("1111");
	game->map_width = 4;
	game->map_height = 4;
	player_orientation(&game->player, 'N');
}

Test(collision, space)
{
	t_game   game;
	t_vector collision;

	game_init(&game);
	create_map_4x4(&game);
	game.player.pos = create_vector(1.5, 1.5);
	collision = check_space_collision(&game, create_vector(0.5, 0.5));
	cr_assert(collision.x == 1);
	cr_assert(collision.y == 1);
	collision = check_space_collision(&game, create_vector(2.5, 2.5));
	cr_assert(collision.x == 1);
	cr_assert(collision.y == 1);
	collision = check_space_collision(&game, create_vector(-0.5, 0.5));
	cr_assert(collision.x == 0);
	cr_assert(collision.y == 1);
	collision = check_space_collision(&game, create_vector(-0.5, -0.5));
	cr_assert(collision.x == 0);
	cr_assert(collision.y == 0);
	destroy_game(&game);
}

Test(collision, wall)
{
	t_game   game;
	t_vector collision;
	t_vector new_pos;

	game_init(&game);
	create_map_4x4(&game);
	game.player.pos = create_vector(1.5, 1.5);
	new_pos = create_vector(0.5, 0.5);
	collision = check_collision(&game, game.player.pos, new_pos,
	                            sub_vector(new_pos, game.player.pos));
	cr_assert(collision.x == 0);
	cr_assert(collision.y == 0);
	game.player.pos = create_vector(1.5, 1.5);
	new_pos = create_vector(2.5, 2.5);
	collision = check_collision(&game, game.player.pos, new_pos,
	                            sub_vector(new_pos, game.player.pos));
	cr_assert(collision.x == 1);
	cr_assert(collision.y == 1);
	destroy_game(&game);
}
