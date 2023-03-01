#include "cub3d.h"
#include "parser.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(init_map, parser, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		char **av;
		int    expected;
	} tt[] = {
	    {"01) no player:", ft_split("./bin maps/invalid/no_player.cub", ' '), 0},
	    {"02) multiple players:", ft_split("./bin maps/invalid/multiple_players1.cub", ' '), 0},
	    {"03) multiple players:", ft_split("./bin maps/invalid/multiple_players2.cub", ' '), 0},
	    {"04) multiple players:", ft_split("./bin maps/invalid/multiple_players3.cub", ' '), 0},
	    {"05) multiple players:", ft_split("./bin maps/invalid/multiple_players4.cub", ' '), 0},
	    {"06) multiple players:", ft_split("./bin maps/invalid/multiple_players5.cub", ' '), 0},
	    {"07) multiple players:", ft_split("./bin maps/invalid/multiple_players6.cub", ' '), 0},
	    {"08) invalid map property:", ft_split("./bin maps/invalid/attr1.cub", ' '), 0},
	    {"09) invalid map property:", ft_split("./bin maps/invalid/attr2.cub", ' '), 0},
	    {"10) invalid map property:", ft_split("./bin maps/invalid/attr3.cub", ' '), 0},
	    {"11) invalid map property:", ft_split("./bin maps/invalid/attr4.cub", ' '), 0},
	    {"12) empty map:", ft_split("./bin maps/invalid/empty1.cub", ' '), 0},
	    {"13) empty map:", ft_split("./bin maps/invalid/empty2.cub", ' '), 0},
	    {"14) empty map:", ft_split("./bin maps/invalid/empty3.cub", ' '), 0},
	    {"15) empty map:", ft_split("./bin maps/invalid/empty4.cub", ' '), 0},
	    {"16) player at N:", ft_split("./bin maps/valid/sample.cub", ' '), 1},
	    {"17) player at S:", ft_split("./bin maps/valid/south.cub", ' '), 1},
	    {"18) player at W:", ft_split("./bin maps/valid/west.cub", ' '), 1},
	    {"19) player at E:", ft_split("./bin maps/valid/east.cub", ' '), 1},
	    {"20) minimum map size:", ft_split("./bin maps/valid/min_map.cub", ' '), 1},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	size_t i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = init_map(&game, tt[i].av);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);

		clean_params(&game.params);
		ft_free_matrix(game.map);
	}
}

Test(init_config_params, texture_parameters, .init = cr_redirect_stdout)
{
	struct s_tt
	{
		char  *name;
		char **av;
		int    expected;
	} tt[] = {
	    {"00) valid texture maps:", ft_split("./bin maps/valid/texture_params0.cub", ' '), 1},
	    {"01) valid texture maps:", ft_split("./bin maps/valid/texture_params1.cub", ' '), 1},
	    {"02) invalid texture file extension:", ft_split("./bin maps/invalid/texture_params2.cub", ' '), 0},
	    {"03) invalid texture file extension:", ft_split("./bin maps/invalid/texture_params3.cub", ' '), 0},
	    {"04) invalid texture file:", ft_split("./bin maps/invalid/texture_params4.cub", ' '), 0},
	    {"05) invalid texture file:", ft_split("./bin maps/invalid/texture_params5.cub", ' '), 0},
	    {"06) invalid identifier:", ft_split("./bin maps/invalid/texture_params6.cub", ' '), 0},
	    {"07) invalid identifier:", ft_split("./bin maps/invalid/texture_params7.cub", ' '), 0},
	    {"08) invalid identifier:", ft_split("./bin maps/invalid/texture_params8.cub", ' '), 0},
	    {"09) invalid identifier:", ft_split("./bin maps/invalid/texture_params9.cub", ' '), 0},
	    {"10) invalid identifier:", ft_split("./bin maps/invalid/texture_params10.cub", ' '), 0},
	    {"11) tab separated:", ft_split("./bin maps/valid/texture_params11.cub", ' '), 1},
	    {"12) tab and space separated:", ft_split("./bin maps/valid/texture_params12.cub", ' '), 1},
	    {"13) space and tab separated:", ft_split("./bin maps/valid/texture_params13.cub", ' '), 1},
	    {"14) duplicated texture:", ft_split("./bin maps/invalid/texture_params14.cub", ' '), 0},
	    {"15) duplicated texture:", ft_split("./bin maps/invalid/texture_params15.cub", ' '), 0},
	    {"16) empty lines between:", ft_split("./bin maps/valid/texture_params16.cub", ' '), 1},
	    {"17) empty lines between:", ft_split("./bin maps/valid/texture_params17.cub", ' '), 1},
	    {"18) empty lines between:", ft_split("./bin maps/valid/texture_params18.cub", ' '), 1},
	    {"19) empty lines between:", ft_split("./bin maps/valid/texture_params19.cub", ' '), 1},
	};
	size_t n = sizeof(tt) / sizeof(tt[0]);

	size_t i = -1;
	while (++i < n)
	{
		t_game game;

		game.map = NULL;
		game_init(&game);

		int got = init_config_params(&game, tt[i].av[1]);
		cr_expect(got == tt[i].expected, "%s expect %d, but got %d", tt[i].name,
		          tt[i].expected, got);
		ft_free_matrix(tt[i].av);

		clean_params(&game.params);
		ft_free_matrix(game.map);
	}
}
